#include <modui/ui/slider/slider.hpp>
#include "../../internal/internal_core.hpp"

#include <cstdio>

namespace modui::ui
{
	Slider::Slider(float min_value, float max_value) : BaseSlider(min_value, max_value),
		_press_factor{0.0f}
	{
		this->_size = Vec2(MODUI_SIZE_WIDTH_FULL, utils::dp(40));
	}

	Slider* Slider::init(float min_value, float max_value) { return new Slider(min_value, max_value); }

	Vec2 Slider::render(Vec2 pos, Vec2 reserved_space)
	{
		const float __ripple_radius = utils::dp(20);
		const float __circle_radius = utils::dp(10);
		const float __slider_thickness = utils::dp(6);

		ImDrawList* draw_list =  ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		this->_pos = pos;

		pos.x += this->_padding.w;
		pos.y += this->_padding.x;
		reserved_space.x -= this->_padding.y;
		reserved_space.x -= this->_padding.w;
		reserved_space.y -= this->_padding.x;
		reserved_space.y -= this->_padding.z;

		Vec2 size = this->_calculated_size;

		float start_x = pos.x + __ripple_radius;
		float end_x = pos.x + size.x - __ripple_radius;
		float center_y = pos.y + size.y / 2.0f;

		float slider_x = utils::map(this->_value, this->_min_value, this->_max_value, start_x, end_x);\

		Vec2 l1_p1 = Vec2(start_x, center_y - __slider_thickness / 2.0f);
		Vec2 l1_p2 = Vec2(slider_x, center_y + __slider_thickness / 2.0f);

		Vec2 l2_p1 = Vec2(slider_x, center_y - __slider_thickness / 2.0f);
		Vec2 l2_p2 = Vec2(end_x, center_y + __slider_thickness / 2.0f);

		ui::BaseSlider::render(Vec2(start_x, center_y - __ripple_radius), Vec2(end_x - start_x, __ripple_radius * 2.0f));

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

		Col32 ripple_color = (theme().primary & 0xFFFFFF) | (unsigned(0xFF * this->_press_factor * 0.1f) << 24);

		draw_list->AddRectFilled(Vec2(slider_x - __ripple_radius, center_y - __ripple_radius), Vec2(slider_x + __ripple_radius, center_y + __ripple_radius), ripple_color, 99999.0f);
		draw_list->AddRectFilled(l1_p1, l1_p2, theme().primary, MODUI_ROUNDING_FULL);
		draw_list->AddRectFilled(l2_p1, l2_p2, (theme().primary & 0xFFFFFF) | 0x61000000, MODUI_ROUNDING_FULL);
		draw_list->AddCircleFilled(Vec2(slider_x, center_y), __circle_radius, theme().primary);

		return pos + size + Vec2(this->_padding.y, this->_padding.z);
	}

	float Slider::calculate_size_x(float reserved_space_x)
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

		this->_calculated_size.x = x;

		return x;
	}

	float Slider::calculate_size_y(float reserved_space_y)
	{
		float y = this->_size.y;

		if (y == MODUI_SIZE_WIDTH_FULL)
		{
			y = reserved_space_y;
		}
		else if (y == MODUI_SIZE_HEIGHT_WRAP)
		{
			y = utils::dp(40) + this->_padding.x + this->_padding.z; 
		}
		else if (y < 0.0f)
		{
			y = reserved_space_y + y;
		}

		this->_calculated_size.y = y;

		return y;
	}
}