#pragma once

#include "../../core/common.hpp"
#include "../widget.hpp"
#include "screen.hpp"

#include <string>
#include <unordered_map>

namespace modui::ui
{
	class ScreenManager : public Widget
	{
	public:
		ScreenManager();
		static ScreenManager* init();

		ScreenManager* set_screen(const std::string& screen_name);
		Screen* get_screen(const std::string& screen_name);

		virtual ScreenManager* add_widget(Widget* screen) override;
		virtual Vec2 render(Vec2 pos, Vec2 reserved_space) override;

	private:
		Screen* _current_screen;
	};
}