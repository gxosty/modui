#include <modui/ui/button/iconbutton.hpp>

namespace modui::ui
{
	IconButton::IconButton(ImageID icon) : BaseButton(),
		_icon{icon},
		_icon_size{ImGui::GetFontSize()},
		_press_factor{0.0f}
	{
		this->_size = Vec2(utils::dp(40), utils::dp(40));
		this->_rounding = this->_size.y / 2.0f;
	}

	IconButton* IconButton::init(ImageID icon) { return new IconButton(icon); }

	IconButton* IconButton::set_icon(ImageID icon) { this->_icon = icon; return this; }

	const ImageID IconButton::get_icon() { return this->_icon; }

	IconButton* IconButton::set_icon_size(float icon_size) { this->_icon_size = icon_size; return this; }

	Vec2 IconButton::render(Vec2 pos, Vec2 reserved_space)
	{
		ImDrawList* draw_list =  ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		Vec2 size = this->_calculated_size;
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

		Vec2 icon_size = Vec2(this->_icon_size, this->_icon_size);
		Vec2 icon_pos = pos + (size - icon_size) / 2.0f;

		// if (this->_icon != nullptr)
			this->_icon->draw(icon_pos, icon_size, theme().on_primary);

		return pos + size;
	}

	float IconButton::calculate_size_x(float reserved_space_x)
	{
		float x = this->_size.x;

		if (x == MODUI_SIZE_WIDTH_FULL)
		{
			x = reserved_space_x;
		}
		else if (x == MODUI_SIZE_WIDTH_WRAP)
		{
			x = this->_icon_size + utils::dp(14) * 2.0f;
		}
		else if (x < 0.0f)
		{
			x = reserved_space_x + x;
		}

		this->_calculated_size.x = x;

		return x;
	}

	float IconButton::calculate_size_y(float reserved_space_y)
	{
		float y = this->_size.y;

		if (y == MODUI_SIZE_WIDTH_FULL)
		{
			y = reserved_space_y;
		}
		else if (y == MODUI_SIZE_HEIGHT_WRAP)
		{
			y = this->_icon_size + utils::dp(14) * 2.0f;
		}
		else if (y < 0.0f)
		{
			y = reserved_space_y + y;
		}

		this->_calculated_size.y = y;

		return y;
	}
}