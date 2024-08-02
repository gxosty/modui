#include <modui/ui/memorytext.hpp>
#include <modui/app.hpp>

#include <cstring>

namespace modui::ui
{
	MemoryText::MemoryText(const char* text) : Widget(),
		_text{text},
		_font_size{ImGui::GetFontSize()}
	{
		this->_size = Vec2(MODUI_SIZE_WIDTH_WRAP, MODUI_SIZE_HEIGHT_WRAP);
		this->_side = modui::SIDE_LEFT;
	}

	MemoryText* MemoryText::init(const char* text) { return new MemoryText(text); }

	MemoryText* MemoryText::set_side(modui::Side side)
	{
		this->_side = side;

		return this;
	}

	MemoryText* MemoryText::set_text(const char* text)
	{
		this->_text = text;

		if (modui::get_current_app()->is_rendering())
			this->_update_text_size();

		return this;
	}

	MemoryText* MemoryText::set_font_size(float font_size)
	{
		this->_font_size = font_size;

		if (modui::get_current_app()->is_rendering())
			this->_update_text_size();

		return this;
	}

	void MemoryText::pre_render()
	{
		this->_update_text_size();

		Widget::pre_render();
	}

	Vec2 MemoryText::render(Vec2 pos, Vec2 reserved_space)
	{
		ImDrawList* draw_list =  ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		Vec2 size = this->_calculated_size;
		this->_pos = pos;

		if (this->_text == nullptr) return pos + size;

		Vec2 text_pos = pos + (size - this->_text_size) / 2.0f;
		text_pos.x += this->_padding.w;
		text_pos.y += this->_padding.x;

		draw_list->AddText(ImGui::GetFont(), this->_font_size, text_pos, this->is_on_card() ? theme().on_surface_variant : theme().on_surface, this->_text, nullptr, size.x);

		return pos + size;
	}

	void MemoryText::_update_text_size(float available_width)
	{
		if ((this->_text == nullptr) || (strlen(this->_text) == 0) || (this->_font_size == 0.0f) || (available_width < 0.0f))
		{
			this->_text_size.x = 0.0f;
			this->_text_size.y = this->_font_size;

			return;
		}

		this->_text_size = ImGui::GetFont()->CalcTextSizeA(this->_font_size, FLT_MAX, available_width, this->_text, nullptr);
		this->_text_size.x += 1.0f;
	}

	Vec2 MemoryText::_calc_side()
	{
		return Vec2(0.0f, 0.0f);
	}

	float MemoryText::calculate_size_x(float reserved_space_x)
	{
		float x = this->_size.x;

		if (x == MODUI_SIZE_WIDTH_FULL)
		{
			x = reserved_space_x;
			this->_update_text_size(x - this->_padding.y - this->_padding.w);
		}
		else if (x == MODUI_SIZE_WIDTH_WRAP)
		{
			this->_update_text_size(reserved_space_x - this->_padding.y - this->_padding.w);
			x = this->_text_size.x + this->_padding.y + this->_padding.w;
		}
		else if (x < 0.0f)
		{
			x = reserved_space_x + x;
			this->_update_text_size(x - this->_padding.y - this->_padding.w);
		}

		this->_calculated_size.x = x;

		return x;
	}

	float MemoryText::calculate_size_y(float reserved_space_y)
	{
		float y = this->_size.y;

		if (y == MODUI_SIZE_WIDTH_FULL)
		{
			y = reserved_space_y;
		}
		else if (y == MODUI_SIZE_HEIGHT_WRAP)
		{
			y = this->_text_size.y + this->_padding.x + this->_padding.z;
		}
		else if (y < 0.0f)
		{
			y = reserved_space_y + y;
		}

		this->_calculated_size.y = y;

		return y;
	}

	bool MemoryText::is_on_card()
	{
		return Widget::is_on_card();
	}
}