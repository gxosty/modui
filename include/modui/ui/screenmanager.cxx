#include <modui/ui/screenmanager.hpp>
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

	ScreenManager* ScreenManager::add(Widget* widget)
	{
		Screen* screen = dynamic_cast<Screen*>(widget);

		if (screen == nullptr) throw exceptions::AddWidgetException("Only `Screen` objects can be added to `ScreenManager`");

		auto ret = Widget::add(widget);

		if (this->_children.size() == 1) this->set_screen(((Screen*)this->_children[0])->get_name());

		return (ScreenManager*)ret;
	}

	Vec2 ScreenManager::render(Vec2 pos, Vec2 reserved_space)
	{
		if (!this->_children.empty())
			this->_current_screen->render(pos, this->_calculated_size);

		return pos + this->_calculated_size;
	}

	float ScreenManager::calculate_size_x(float reserved_space_x)
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

	float ScreenManager::calculate_size_y(float reserved_space_y)
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