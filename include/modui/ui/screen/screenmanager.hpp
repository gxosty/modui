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

		ScreenManager* set_screen(const std::string& screen_name) override;
		Screen* get_screen(const std::string& screen_name);

		ScreenManager* add(Widget* screen) override;
		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		float calculate_size_x(float reserved_space_x) override;
		float calculate_size_y(float reserved_space_y) override;

	private:
		Screen* _current_screen;
	};
}