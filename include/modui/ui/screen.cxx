#include <modui/ui/screen.hpp>
#include <modui/core/exceptions.hpp>

namespace modui::ui
{
	Screen::Screen(const std::string& name) : Widget(),
		_name{name} {}

	Screen* Screen::init(const std::string& name) { return new Screen(name); }

	Screen* Screen::set_name(const std::string& name)
	{
		this->_name = name;

		return this;
	}

	const std::string& Screen::get_name()
	{
		return this->_name;
	}

	Screen* Screen::add(Widget* widget)
	{
		if (!this->_children.empty())
			throw exceptions::AddWidgetException("Only one widget can be added to `modui::ui::Screen` object");

		return (Screen*)Widget::add(widget);
	}

	Vec2 Screen::render(Vec2 pos, Vec2 reserved_space)
	{
		if (!this->_children.empty())
			this->_children[0]->render(pos, this->_calculated_size);

		return pos + this->_calculated_size;
	}

	float Screen::calculate_size_x(float reserved_space_x)
	{
		float x = this->_size.x;

		if ((x == MODUI_SIZE_WIDTH_FULL) || (x == MODUI_SIZE_WIDTH_WRAP))
		{
			x = reserved_space_x;
		}
		else if (x < 0.0f)
		{
			x = reserved_space_x + x;
		}

		if (!this->_children.empty()) this->_children[0]->calculate_size_x(x);
		this->_calculated_size.x = x;

		return x;
	}

	float Screen::calculate_size_y(float reserved_space_y)
	{
		float y = this->_size.y;

		if ((y == MODUI_SIZE_WIDTH_FULL) || (y == MODUI_SIZE_HEIGHT_WRAP))
		{
			y = reserved_space_y;
		}
		else if (y < 0.0f)
		{
			y = reserved_space_y + y;
		}

		if (!this->_children.empty()) this->_children[0]->calculate_size_y(y);
		this->_calculated_size.y = y;

		return y;
	}
}