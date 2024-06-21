#include <modui/ui/screen/screenmanager.hpp>

#include <modui/core/exceptions.hpp>

namespace modui::ui
{
	ScreenManager::ScreenManager() : Widget() {}

	ScreenManager* ScreenManager::init() { return new ScreenManager(); }

	ScreenManager* ScreenManager::set_screen(const std::string& screen_name)
	{
		Screen* screen = this->get_screen(screen_name);

		if (screen == nullptr) throw exceptions::ScreenNotFoundException(screen_name);

		this->_current_screen = screen;

		return this;
	}

	Screen* ScreenManager::get_screen(const std::string &screen_name)
	{
		for (auto child : this->_children)
		{
			if (((Screen*)child)->get_name() == screen_name) return (Screen*)child;
		}

		return nullptr;
	}

	ScreenManager* ScreenManager::add_widget(Widget* widget)
	{
		Screen* screen = dynamic_cast<Screen*>(widget);

		if (screen == nullptr) throw exceptions::AddWidgetException("Only `Screen` objects can be added to `ScreenManager`");

		auto ret = Widget::add_widget(widget);

		if (this->_children.size() == 1) this->set_screen(((Screen*)this->_children[0])->get_name());

		return (ScreenManager*)ret;
	}

	Vec2 ScreenManager::render(Vec2 pos, Vec2 reserved_space)
	{
		if (!this->_children.empty())
			this->_current_screen->render(pos, reserved_space);

		return pos + reserved_space;
	}
}