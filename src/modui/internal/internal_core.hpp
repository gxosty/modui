#pragma once

#include <modui/app.hpp>

#define MODUI_WIDGET_PRESS_TRANSITION_SPEED 1 / 0.08f // 80 millis
#define MODUI_WIDGET_OUTLINE_WIDTH utils::dp(1)

#define MODUI_WIDGET_SLIDER_THICKNESS utils::dp(3)
#define MODUI_WIDGET_SLIDER_CIRCLE_RADIUS utils::dp(5)

namespace modui::internal
{
	void __set_current_app(App* app);
}