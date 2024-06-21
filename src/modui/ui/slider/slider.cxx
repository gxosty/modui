#include <modui/ui/slider/slider.hpp>
#include "../../internal/internal_core.hpp"

#include <iostream>

namespace modui::ui
{
	Slider::Slider(float min_value, float max_value) : BaseSlider(min_value, max_value),
		_press_factor{0.0f}
	{
		this->_size = Vec2(0.0f, utils::dp(20));
	}

	Slider* Slider::init(float min_value, float max_value) { return new Slider(min_value, max_value); }

	Vec2 Slider::render(Vec2 pos, Vec2 reserved_space)
	{
		static const float __ripple_radius = utils::dp(10);

		ImDrawList* draw_list =  ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		this->_pos = pos;

		pos.x += this->_padding.w;
		pos.y += this->_padding.x;
		reserved_space.x -= this->_padding.y;
		reserved_space.x -= this->_padding.w;
		reserved_space.y -= this->_padding.x;
		reserved_space.y -= this->_padding.z;

		Vec2 size = this->_size;

		if (size.x <= 0.0f)
		{
			size.x = reserved_space.x + (size.x == MODUI_SIZE_WIDTH_FULL ? 0.0f : size.x);
		}

		if (size.y <= 0.0f)
		{
			size.y = reserved_space.y + (size.y == MODUI_SIZE_HEIGHT_FULL ? 0.0f : size.y);
		}

		float start_x = pos.x + MODUI_WIDGET_SLIDER_CIRCLE_RADIUS;
		float end_x = pos.x + size.x - MODUI_WIDGET_SLIDER_CIRCLE_RADIUS;
		float center_y = pos.y + size.y / 2.0f;
		float slider_x = utils::map(this->_value, this->_min_value, this->_max_value, start_x, end_x);\

		Vec2 l1_p1 = Vec2(start_x, center_y - MODUI_WIDGET_SLIDER_THICKNESS / 2.0f);
		Vec2 l1_p2 = Vec2(slider_x, center_y + MODUI_WIDGET_SLIDER_THICKNESS / 2.0f);

		Vec2 l2_p1 = Vec2(slider_x, center_y - MODUI_WIDGET_SLIDER_THICKNESS / 2.0f);
		Vec2 l2_p2 = Vec2(end_x, center_y + MODUI_WIDGET_SLIDER_THICKNESS / 2.0f);

		ui::BaseSlider::render(Vec2(start_x, center_y - MODUI_WIDGET_SLIDER_CIRCLE_RADIUS), Vec2(end_x - start_x, MODUI_WIDGET_SLIDER_CIRCLE_RADIUS * 2.0f));

		this->_press_factor = utils::clamp(
			this->_press_factor + (ImGui::GetIO().DeltaTime * MODUI_WIDGET_PRESS_TRANSITION_SPEED) * (this->_is_held ? 1.0f : -1.0f),
			0.0f,
			1.0f
		);

		Col4 fill_color = utils::mix(
			utils::Col32to4(theme().primary),
			utils::add_button_pressed_layer(
				utils::Col32to4(theme().primary),
				utils::Col32to4(theme().on_primary)
			),
			this->_press_factor
		);

		Col4 ripple_color = utils::mix(
			utils::Col32to4(0x0),
			utils::add_button_pressed_layer(
				utils::Col32to4(0x0),
				utils::Col32to4(theme().on_primary)
			),
			this->_press_factor
		);

		draw_list->AddRectFilled(Vec2(slider_x - __ripple_radius, center_y - __ripple_radius), Vec2(slider_x + __ripple_radius, center_y + __ripple_radius), utils::Col4to32(ripple_color), 99999.0f);
		draw_list->AddRectFilled(l1_p1, l1_p2, theme().primary, MODUI_ROUNDING_FULL);
		draw_list->AddRectFilled(l2_p1, l2_p2, (theme().primary & 0xFFFFFF) | 0x61000000, MODUI_ROUNDING_FULL);
		draw_list->AddCircleFilled(Vec2(slider_x, center_y), MODUI_WIDGET_SLIDER_CIRCLE_RADIUS, theme().primary);

		return pos + size + Vec2(this->_padding.y, this->_padding.z);
	}
}