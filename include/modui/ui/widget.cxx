#include <modui/ui/widget.hpp>
#include <modui/app.hpp>
#include "../internal/internal_utils.hpp"

#include <cstdarg>

namespace modui::ui
{
	Widget::Widget() :
		_id{modui::internal::__get_next_id_for_widget()},
		_pos{0.0f, 0.0f},
		_size{MODUI_SIZE_WIDTH_FULL, MODUI_SIZE_HEIGHT_FULL},
		_padding{0.0f, 0.0f, 0.0f, 0.0f},
		_spacing{0.0f, 0.0f},
		_root_widget{nullptr}
		{
			modui::App* app = modui::get_current_app();
			this->_theme = &app->_current_theme;
			this->_calculated_size = _size;
		};

	Widget::~Widget() {};

	Widget* Widget::init() { return new Widget(); }

	Widget* Widget::add(Widget* widget)
	{
		widget->_set_parent(this);

		if (this->_root_widget)
			widget->_set_root_widget(this->_root_widget);

		this->_children.push_back(widget);
		return this;
	}

	Widget* Widget::remove(Widget* widget)
	{
		if (this->_children.empty())
		{
			return this;
		}

		for (auto i = this->_children.begin(); i < this->_children.end(); i++)
		{
			if (*i == widget)
			{
				this->_children.erase(i);
				delete widget;
				break;
			}
		}

		return this;
	}

	Widget* Widget::set_id(const std::string& id)
	{
		this->_name_id = id;

		return this;
	}

	const std::string& Widget::get_id()
	{
		return this->_name_id;
	}

	Widget* Widget::find_widget_by_id(const std::string& id)
	{
		for (auto child : this->_children)
		{
			if (!child->get_id().empty())
			{
				if (child->get_id() == id) return child;
			}

			child = child->find_widget_by_id(id);

			if (child != nullptr) return child;
		}

		return nullptr;
	}

	Widget* Widget::get_parent()
	{
		return reinterpret_cast<Widget*>(this->_parent);
	}

	Vec2 Widget::get_pos()
	{
		return this->_pos;
	}

	Widget* Widget::set_size(const Vec2& size)
	{
		this->_size = size;

		return this;
	}

	Widget* Widget::set_size_x(float x)
	{
		this->_size.x = x;

		return this;
	}

	Widget* Widget::set_size_y(float y)
	{
		this->_size.y = y;

		return this;
	}

	Vec2 Widget::get_size()
	{
		return this->_size;
	}

	Vec2 Widget::get_calculated_size()
	{
		return this->_calculated_size;
	}

	Theme& Widget::get_theme()
	{
		return **this->_theme;
	}

	void Widget::pre_render()
	{
		for (auto& child : this->_children)
		{
			child->pre_render();
		}
	}

	void Widget::post_render()
	{
		for (auto& child : this->_children)
		{
			child->post_render();
		}
	}

	Vec2 Widget::render(Vec2 pos, Vec2 reserved_space)
	{
		this->_pos = pos;
		Vec2 size = this->_calculated_size;
		ImGui::SetCursorPos(this->_pos);
		ImGui::Dummy(size);
		return pos + size;
	}

	void Widget::_set_parent(core::BaseWidget* bwidget)
	{
		this->_parent = bwidget;
	}

	Widget* Widget::build_widget()
	{
		this->on_create_widget();
		this->_set_root_widget(nullptr);

		return this;
	}

	void Widget::on_create_widget() { return; }

	void Widget::_set_root_widget(Widget* widget)
	{
		if (widget != nullptr)
		{
			widget->_root_widget = this;
		}
		else
		{
			widget = this;
		}

		for (auto child : widget->_children)
		{
			this->_set_root_widget(child);
		}
	}

	Vec2 Widget::calculate_size(Vec2 reserved_space) {
		this->calculate_size_x(reserved_space.x);
		this->calculate_size_y(reserved_space.y);

		return this->_calculated_size;
	}

	float Widget::calculate_size_x(float reserved_space_x)
	{
		float x = this->_size.x;

		if (x == MODUI_SIZE_WIDTH_FULL)
		{
			x = reserved_space_x;
		}
		else if (x == MODUI_SIZE_WIDTH_WRAP)
		{
			x = 0.0f;
		}
		else if (x < 0.0f)
		{
			x = reserved_space_x + x;
		}

		this->_calculated_size.x = x;

		return x;
	}

	float Widget::calculate_size_y(float reserved_space_y)
	{
		float y = this->_size.y;

		if (y == MODUI_SIZE_WIDTH_FULL)
		{
			y = reserved_space_y;
		}
		else if (y == MODUI_SIZE_HEIGHT_WRAP)
		{
			y = 0.0f;
		}
		else if (y < 0.0f)
		{
			y = reserved_space_y + y;
		}

		this->_calculated_size.y = y;

		return y;
	}

	void Widget::push_on_card()
	{
		Widget::_on_card++;
	}

	void Widget::pop_on_card()
	{
		Widget::_on_card--;
	}

	bool Widget::is_on_card()
	{
		return Widget::_on_card > 0;
	}

	int Widget::_on_card = 0;
}



// These are less likely to interest you
namespace modui::ui
{
	Widget* Widget::set_orientation(modui::LayoutOrientation orientation) { return this; }
	Widget* Widget::set_side(modui::Side side) { return this; }

	Widget* Widget::on_press(ButtonInputCallback callback) { return this; }
	Widget* Widget::on_hold(ButtonInputCallback callback) { return this; }
	Widget* Widget::on_release(ButtonInputCallback callback) { return this; }
	Widget* Widget::on_slide(ButtonInputCallback callback) { return this; }

	Widget* Widget::set_text(const std::string& text) { return this; }
	Widget* Widget::set_supporting_text(const std::string& supporting_text) { return this; }
	Widget* Widget::set_trailing_text(const std::string& trailing_text) { return this; }
	Widget* Widget::set_font_size(float font_size) { return this; }

	Widget* Widget::set_icon(ImageID icon) { return this; }
	Widget* Widget::set_leading_icon(ImageID leading_icon) { return this; }
	Widget* Widget::set_icon_size(float icon_size) { return this; }

	Widget* Widget::set_trailing_widget(Widget* trailing_widget) { return this; }

	Widget* Widget::set_value(float value) { return this; }
	Widget* Widget::set_state(bool state) { return this; }
	bool    Widget::get_state() { return false; }
	Widget* Widget::set_toggleable(bool toggleable) { return this; }

	Widget* Widget::set_padding(Vec2 padding) { this->_padding = Vec4(padding.y, padding.x, padding.y, padding.x); return this; }
	Widget* Widget::set_padding(Vec4 padding) { this->_padding = padding; return this; }
	Widget* Widget::set_padding(float x, float y) { this->_padding = Vec4(y, x, y, x); return this; }
	Widget* Widget::set_padding(float top, float right, float bottom, float left) { this->_padding = Vec4(top, right, bottom, left); return this; }
	Widget* Widget::set_padding(float padding) { this->_padding = Vec4(padding, padding, padding, padding); return this; }
	Widget* Widget::set_padding_top(float padding) { this->_padding.x = padding; return this; }
	Widget* Widget::set_padding_right(float padding) { this->_padding.y = padding; return this; }
	Widget* Widget::set_padding_bottom(float padding) { this->_padding.z = padding; return this; }
	Widget* Widget::set_padding_left(float padding) { this->_padding.w = padding; return this; }
	Vec4    Widget::get_padding() { return this->_padding; }
	Widget* Widget::set_spacing(Vec2 spacing) { this->_spacing = spacing; return this; }
	Widget* Widget::set_spacing(float x, float y) { this->_spacing = Vec2(x, y); return this; }
	Widget* Widget::set_spacing(float spacing) { this->_spacing = Vec2(spacing, spacing); return this; }
	Vec2    Widget::get_spacing() { return this->_spacing; }

	Widget* Widget::set_name(const std::string& name) { return this; }
	Widget* Widget::set_screen(const std::string& screen_name) { return this; }
}