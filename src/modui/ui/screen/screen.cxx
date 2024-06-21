#include <modui/ui/screen/screen.hpp>

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

	Screen* Screen::add_widget(Widget* widget)
	{
		if (!this->_children.empty())
			throw exceptions::AddWidgetException("Only one widget can be added to `modui::ui::Screen` object");

		return (Screen*)Widget::add_widget(widget);
	}

	Vec2 Screen::render(Vec2 pos, Vec2 reserved_space)
	{
		if (!this->_children.empty())
			this->_children[0]->render(pos, reserved_space);

		return pos + reserved_space;
	}
}