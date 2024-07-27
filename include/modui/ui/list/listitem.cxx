#include <modui/ui/list/listitem.hpp>
#include <modui/app.hpp>
#include <modui/core/image/image.hpp>

#include <cstdio>

namespace modui::ui
{
	ListItem::ListItem(
		const std::string& text,
		const std::string& supporting_text,
		const std::string& trailing_text,
		ImageID leading_icon,
		Widget* trailing_widget,
		Type type
	) : BaseButton(),
		_trailing_widget{trailing_widget},
		_type{type},
		_state{true},
		_leading_icon_size{0.0f},
		_text_size{0.0f, 0.0f},
		_supporting_text_size{0.0f, 0.0f},
		_trailing_text_size{0.0f, 0.0f},
		_font_size{ImGui::GetFontSize()}
	{
		this->_size = Vec2(MODUI_SIZE_WIDTH_FULL, MODUI_SIZE_HEIGHT_WRAP);
		this->set_text(text);
		this->set_supporting_text(supporting_text);
		this->set_trailing_text(trailing_text);
		this->set_leading_icon(leading_icon);
	}

	ListItem* ListItem::init(
		const std::string& text,
		const std::string& supporting_text,
		const std::string& trailing_text,
		ImageID leading_icon,
		Widget* trailing_widget,
		Type type	
	) { return new ListItem(text, supporting_text, trailing_text, leading_icon, trailing_widget, type); }

	ListItem* ListItem::set_text(const std::string& text)
	{
		this->_text = text;

		if (modui::get_current_app()->is_rendering())
			this->_update_text_size();

		return this;
	}

	const std::string& ListItem::get_text() const
	{
		return this->_text;
	}

	ListItem* ListItem::set_supporting_text(const std::string& supporting_text)
	{
		this->_supporting_text = supporting_text;

		if (modui::get_current_app()->is_rendering())
			this->_update_supporting_text_size();

		return this;
	}

	const std::string& ListItem::get_supporting_text() const
	{
		return this->_supporting_text;
	}

	ListItem* ListItem::set_trailing_text(const std::string& trailing_text)
	{
		this->_trailing_text = trailing_text;

		if (modui::get_current_app()->is_rendering())
			this->_update_trailing_text_size();

		return this;
	}

	const std::string& ListItem::get_trailing_text() const
	{
		return this->_trailing_text;
	}

	ListItem* ListItem::set_leading_icon(ImageID leading_icon)
	{
		this->_leading_icon = leading_icon;

		if (modui::get_current_app()->is_rendering())
			this->_update_leading_icon_size();

		return this;
	}

	ImageID ListItem::get_leading_icon() const
	{
		return this->_leading_icon;
	}

	ListItem* ListItem::set_trailing_widget(Widget* trailing_widget)
	{
		this->_trailing_widget = trailing_widget;

		if (trailing_widget != nullptr)
			trailing_widget->pre_render();

		return this;
	}

	Widget* ListItem::get_trailing_widget() const
	{
		return this->_trailing_widget;
	}

	void ListItem::pre_render()
	{
		this->_update_text_size();
		this->_update_supporting_text_size();
		this->_update_trailing_text_size();
		this->_update_leading_icon_size();

		if (this->_trailing_widget != nullptr)
			this->_trailing_widget->pre_render();

		Widget::pre_render();
	}

	Vec2 ListItem::render(Vec2 pos, Vec2 reserved_space)
	{
		ImDrawList* draw_list =  ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		this->_pos = pos;
		Vec2 size = this->_calculated_size;

		ui::BaseButton::render(pos, size);

		this->_press_factor = utils::clamp(
			this->_press_factor + (ImGui::GetIO().DeltaTime * MODUI_WIDGET_PRESS_TRANSITION_SPEED) * (this->_is_held ? 1.0f : -1.0f),
			0.0f,
			1.0f
		);

		Vec2 text_pos, supporting_text_pos, trailing_text_pos,
				leading_icon_pos, trailing_widget_pos;

		this->_get_all_pos(text_pos, supporting_text_pos, trailing_text_pos, leading_icon_pos, trailing_text_pos);

		text_pos += pos;
		leading_icon_pos += pos;

		Col32 container_fill_color = theme().surface;
		Col32 leading_icon_color = (theme().on_surface_variant & 0xFFFFFF);
		Col32 text_color = (theme().on_surface & 0xFFFFFF);
		Col32 ripple_color = (theme().on_surface & 0xFFFFFF) | (unsigned(0xFF * this->_press_factor * 0.1f) << 24);

		if (this->_state)
		{
			text_color |= unsigned(0xFF) << 24;
			leading_icon_color |= unsigned(0xFF) << 24;
		}
		else
		{
			text_color |= unsigned(0x61) << 24;
			leading_icon_color |= unsigned(0x61) << 24;
		}

		if (this->_leading_icon != nullptr)
		{
			this->_leading_icon->draw(leading_icon_pos, Vec2(_leading_icon_size, _leading_icon_size), leading_icon_color);
		}

		draw_list->AddText(ImGui::GetFont(), this->_font_size, text_pos, text_color, this->_text.c_str());

		draw_list->AddRectFilled(
			pos,
			pos + size,
			ripple_color
		);

		return pos + size;
	}

	float ListItem::calculate_size_x(float reserved_space_x)
	{
		float x = this->_size.x;

		if (x == MODUI_SIZE_WIDTH_FULL)
		{
			x = reserved_space_x;
		}
		else if (x == MODUI_SIZE_WIDTH_WRAP)
		{
			bool anything_before = false;
			x = utils::dp(16) * 2.0f;

			if (this->_leading_icon != nullptr)
			{
				x += this->_leading_icon_size;

				anything_before = true;
			}

			if (!this->_text.empty())
			{
				if (anything_before) x += utils::dp(16);

				x += this->_text_size.x;
				anything_before = true;
			}

			if (!this->_supporting_text.empty())
			{
				if (this->_text.empty() && anything_before) x += utils::dp(16);

				x += fmax(this->_supporting_text_size.x - this->_text_size.x, 0.0f);
				anything_before = true;
			}

			if (this->_trailing_widget != nullptr)
			{
				if (anything_before) x += utils::dp(16);
				x += this->_trailing_widget->calculate_size_x(0.0f); // widget width should be WRAP
			}
			else if (!this->_trailing_text.empty())
			{
				if (anything_before) x += utils::dp(16);
				x += this->_trailing_text_size.x;
			}

			x = fmin(x, reserved_space_x);
		}
		else if (x < 0.0f)
		{
			x = reserved_space_x + x;
		}

		this->_calculated_size.x = x;

		return x;
	}

	float ListItem::calculate_size_y(float reserved_space_y)
	{
		float y = this->_size.y;

		if (y == MODUI_SIZE_WIDTH_FULL)
		{
			y = reserved_space_y;
		}
		else if (y == MODUI_SIZE_HEIGHT_WRAP)
		{
			switch (this->_type)
			{
			case Type::ONE_LINED:
				y = utils::dp(8) * 2.0f + this->_leading_icon_size;
				y = fmax(y, utils::dp(56));
				break;
			case Type::TWO_LINED:
				y = utils::dp(8) * 2.0f + this->_leading_icon_size;
				y = fmax(y, utils::dp(72));
				break;
			case Type::THREE_LINED:
				y = utils::dp(12) * 2.0f + this->_leading_icon_size;
				y = fmax(y, utils::dp(88));
				break;
			}
		}
		else if (y < 0.0f)
		{
			y = reserved_space_y + y;
		}

		
		this->_calculated_size.y = y;

		return y;
	}

	void ListItem::_update_text_size()
	{
		if (this->_text.empty() || this->_font_size == 0.0f)
		{
			this->_text_size.x = 0.0f;
			this->_text_size.y = 0.0f;

			return;
		}

		this->_text_size = ImGui::GetFont()->CalcTextSizeA(this->_font_size, FLT_MAX, 0.0f, this->_text.c_str(), nullptr);
	}

	void ListItem::_update_supporting_text_size()
	{
		if (this->_supporting_text.empty() || this->_font_size == 0.0f)
		{
			this->_supporting_text_size.x = 0.0f;
			this->_supporting_text_size.y = 0.0f;

			return;
		}

		this->_supporting_text_size = ImGui::GetFont()->CalcTextSizeA(this->_supporting_text_font_size, FLT_MAX, 0.0f, this->_supporting_text.c_str(), nullptr);
	}

	void ListItem::_update_trailing_text_size()
	{
		if (this->_trailing_text.empty() || this->_font_size == 0.0f)
		{
			this->_trailing_text_size.x = 0.0f;
			this->_trailing_text_size.y = 0.0f;

			return;
		}

		this->_trailing_text_size = ImGui::GetFont()->CalcTextSizeA(this->_trailing_text_font_size, FLT_MAX, 0.0f, this->_trailing_text.c_str(), nullptr);
	}

	void ListItem::_update_leading_icon_size()
	{
		if (this->_leading_icon == nullptr)
		{
			this->_leading_icon_size = 0.0f;
			return;
		}

		switch (this->_leading_icon->get_image_type())
		{
		case modui::image::ImageType::RASTER_IMAGE:
		case modui::image::ImageType::VECTOR_IMAGE:
			this->_leading_icon_size = utils::dp(56);
			break;
		case modui::image::ImageType::ICON:
			this->_leading_icon_size = utils::dp(24);
			break;
		case modui::image::ImageType::AVATAR:
			this->_leading_icon_size = utils::dp(40);
			break;
		default:
			this->_leading_icon_size = 0.0f;
			break;
		}
	}

	void ListItem::_get_all_pos(
		Vec2& text_pos,
		Vec2& supporting_text_pos,
		Vec2& trailing_text_pos,
		Vec2& leading_icon_pos,
		Vec2& trailing_widget_pos)
	{
		Vec2 size = this->_calculated_size;

		text_pos = {utils::dp(16), 0.0f};
		leading_icon_pos = {utils::dp(16), 0.0f};

		if (this->_leading_icon != nullptr)
		{
			text_pos.x += this->_leading_icon_size + utils::dp(16);
		}

		switch (this->_type)
		{
		case Type::ONE_LINED:
			text_pos.y = (size.y - this->_text_size.y) / 2.0f;
			leading_icon_pos.y = (size.y - this->_leading_icon_size) / 2.0f;
			break;

		case Type::TWO_LINED:
			text_pos.y = (size.y - this->_text_size.y) / 2.0f;
			leading_icon_pos.y = (size.y - this->_leading_icon_size) / 2.0f;
			break;

		case Type::THREE_LINED:
			break;
		}
	}
}