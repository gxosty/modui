#include <modui/ui/button.hpp>
#include <modui/app.hpp>

#include <cmath>
#include <cstdio>

namespace modui::ui
{
	Button::Button(const std::string& text) : BaseButton(),
		_font_size{ImGui::GetFontSize()},
		_press_factor{0.0f}
	{
		this->_size = Vec2(MODUI_SIZE_WIDTH_WRAP, utils::dp(40));
		this->_rounding = this->_size.y / 2.0f;
		this->set_text(text);
	}

	Button* Button::init(const std::string& text) { return new Button(text); }

	Button* Button::set_text(const std::string& text)
	{
		this->_text = text;

		if (modui::get_current_app()->is_rendering())
			this->_update_text_size_v();

		return this;
	}

	Button* Button::set_font_size(float font_size)
	{
		this->_font_size = font_size;

		if (modui::get_current_app()->is_rendering())
			this->_update_text_size_v();

		return this;
	}

	const std::string& Button::get_text()
	{
		return this->_text;
	}

	void Button::pre_render()
	{
		this->_update_text_size_v();

		Widget::pre_render();
	}

	Vec2 Button::render(Vec2 pos, Vec2 reserved_space)
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		Vec2 size = this->_calculated_size;
		// printf("(%.2f, %.2f)\n", size.x, size.y);
		this->_pos = pos;

		ui::BaseButton::render(pos, size);

		this->_press_factor = utils::clamp(
			this->_press_factor + (ImGui::GetIO().DeltaTime * MODUI_WIDGET_PRESS_TRANSITION_SPEED) * (this->_is_held ? 1.0f : -1.0f),
			0.0f,
			1.0f
		);

		Col4 fill_color = utils::Col32to4(theme().primary);
		Col32 ripple_color = (theme().on_primary & 0xFFFFFF) | (unsigned(0xFF * this->_press_factor * 0.1f) << 24);

		draw_list->AddRectFilled(
			pos,
			pos + size,
			utils::Col4to32(fill_color),
			this->_rounding
		);

		draw_list->AddRectFilled(
			pos,
			pos + size,
			ripple_color,
			this->_rounding
		);

		Vec2 text_pos = pos + (size - this->_text_size_v) / 2.0f;

		draw_list->AddText(ImGui::GetFont(), this->_font_size, text_pos, theme().on_primary, this->_text.c_str());

		return pos + size;
	}

	void Button::_update_text_size_v()
	{
		if (this->_text.empty() || this->_font_size == 0.0f)
		{
			this->_text_size_v.x = 0.0f;
			this->_text_size_v.y = 0.0f;

			return;
		}

		this->_text_size_v = ImGui::GetFont()->CalcTextSizeA(this->_font_size, FLT_MAX, 0.0f, this->_text.c_str(), nullptr);
	}

	float Button::calculate_size_x(float reserved_space_x)
	{
		float x = this->_size.x;

		if (x == MODUI_SIZE_WIDTH_FULL)
		{
			x = reserved_space_x;
		}
		else if (x == MODUI_SIZE_WIDTH_WRAP)
		{
			x = this->_text_size_v.x + utils::dp(28) * 2.0f;
		}
		else if (x < 0.0f)
		{
			x = reserved_space_x + x;
		}

		this->_calculated_size.x = x;

		return x;
	}

	float Button::calculate_size_y(float reserved_space_y)
	{
		float y = this->_size.y;

		if (y == MODUI_SIZE_WIDTH_FULL)
		{
			y = reserved_space_y;
		}
		else if (y == MODUI_SIZE_HEIGHT_WRAP)
		{
			y = this->_text_size_v.y + utils::dp(14) * 2.0f;
		}
		else if (y < 0.0f)
		{
			y = reserved_space_y + y;
		}

		this->_calculated_size.y = y;

		return y;
	}
}