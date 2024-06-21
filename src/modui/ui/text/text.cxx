#include <modui/ui/text/text.hpp>
#include "../../internal/internal_core.hpp"

namespace modui::ui
{
	Text::Text(const std::string& text) : Widget(),
		_text{text},
		_font_size{utils::dp(8)}
	{
		this->_size = Vec2(0.0f, 0.0f);
		this->_side = modui::SIDE_LEFT;
	}

	Text* Text::init(const std::string& text) { return new Text(text); }

	Text* Text::set_side(modui::Side side)
	{
		this->_side = side;

		return this;
	}

	Text* Text::set_text(const std::string& text)
	{
		this->_text = text;

		if (modui::get_current_app()->is_rendering())
			this->_update_text_size_v();

		return this;
	}

	Text* Text::set_font_size(float font_size)
	{
		this->_font_size = font_size;

		if (modui::get_current_app()->is_rendering())
			this->_update_text_size_v();

		return this;
	}

	void Text::pre_render()
	{
		this->_update_text_size_v();

		Widget::pre_render();
	}

	Vec2 Text::render(Vec2 pos, Vec2 reserved_space)
	{
		ImDrawList* draw_list =  ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		Vec2 size = this->_size;

		if (size.x == 0.0f)
		{
			size.x = this->_text_size_v.x;
		}
		else if (size.x < 0.0f)
		{
			size.x = reserved_space.x + (size.x == MODUI_SIZE_WIDTH_FULL ? 0.0f : size.x) - this->_padding.y - this->_padding.w;
		}

		if (size.y == 0.0f)
		{
			size.y = this->_text_size_v.y;
		}
		else if (size.y < 0.0f)
		{
			size.y = reserved_space.y + (size.y == MODUI_SIZE_HEIGHT_FULL ? 0.0f : size.y) - this->_padding.x - this->_padding.z;
		}

		this->_pos = pos;

		Vec2 text_pos = pos + (size - this->_text_size_v) / 2.0f;
		text_pos.x += this->_padding.w;
		text_pos.y += this->_padding.x;

		draw_list->AddText(ImGui::GetFont(), this->_font_size, text_pos, theme().on_surface, this->_text.c_str());

		return pos + size + Vec2(this->_padding.y + this->_padding.w, this->_padding.x + this->_padding.z);
	}

	void Text::_update_text_size_v()
	{
		if (this->_text.empty() || this->_font_size == 0.0f)
		{
			this->_text_size_v.x = 0.0f;
			this->_text_size_v.y = 0.0f;

			return;
		}

		this->_text_size_v = ImGui::CalcTextSize(this->_text.c_str()) * (this->_font_size / ImGui::GetFontSize());
	}

	Vec2 Text::_calc_side()
	{
		return Vec2(0.0f, 0.0f);
	}
}