#include <modui/ui/checkbox/checkbox.hpp>
#include "../../internal/internal_core.hpp"

namespace modui::ui
{
	Checkbox::Checkbox(bool state) : BaseButton(),
		_state{state},
		_rounding{utils::dp(1)}
	{
		this->_size = Vec2(utils::dp(20), utils::dp(20));
		BaseButton::on_release(MODUI_CALLBACK(this) {
			this->set_state(!this->get_state());
		});
	}

	Checkbox* Checkbox::init(bool state) { return new Checkbox(state); }

	Checkbox* Checkbox::set_state(bool state)
	{
		this->_state = state;

		return this;
	}

	bool Checkbox::get_state()
	{
		return this->_state;
	}

	Widget* Checkbox::on_release(ButtonInputCallback callback)
	{
		BaseButton::on_release(MODUI_CALLBACK(this, callback) {
			this->set_state(!this->get_state());
			callback(this);
		});

		return this;
	}

	Vec2 Checkbox::render(Vec2 pos, Vec2 reserved_space)
	{
		static const Vec2 box_size = Vec2(utils::dp(10), utils::dp(10));

		ImDrawList* draw_list =  ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		Vec2 size = this->_size;
		this->_pos = pos;

		ui::BaseButton::render(pos, size);

		this->_press_factor = utils::clamp(
			this->_press_factor + (ImGui::GetIO().DeltaTime * MODUI_WIDGET_PRESS_TRANSITION_SPEED) * (this->_is_held ? 1.0f : -1.0f),
			0.0f,
			1.0f
		);

		Col4 outline_color, fill_color;
		Col32 ripple_color;

		ripple_color = (theme().primary & 0xFFFFFF) | (unsigned(0xFF * this->_press_factor * 0.1f) << 24);
		outline_color = utils::Col32to4(ripple_color);

		if (this->_state)
		{
			fill_color = utils::Col32to4(theme().primary);
			outline_color = utils::Col32to4(theme().primary);
		}
		else
		{
			fill_color = Vec4(0.0f, 0.0f, 0.0f, 0.0f);

			outline_color = utils::mix(
				utils::Col32to4(theme().on_surface_variant),
				utils::add_button_pressed_layer(
					utils::Col32to4(theme().on_surface_variant),
					utils::Col32to4(theme().on_surface)
				),
				this->_press_factor
			);
		}

		Vec2 box_pos = pos + (size - box_size) / 2.0f;

		draw_list->AddRectFilled(pos, pos + size, ripple_color, 99999.0f);

		draw_list->AddRectFilled(box_pos, box_pos + box_size, utils::Col4to32(fill_color), this->_rounding);
		draw_list->AddRect(box_pos, box_pos + box_size, utils::Col4to32(outline_color), this->_rounding, 0, MODUI_WIDGET_OUTLINE_WIDTH);

		if (this->_state)
		{
			Vec2 l1_p1 = Vec2(box_pos.x + utils::dp(2), box_pos.y + box_size.y / 2.0f);
			Vec2 l1_p2 = Vec2(box_pos.x + box_size.x / 2.0f - utils::dp(1), box_pos.y + box_size.y - utils::dp(2.5));

			Vec2 l2_p1 = l1_p2;
			Vec2 l2_p2 = Vec2(box_pos.x + box_size.x - utils::dp(2), box_pos.y + utils::dp(2));

			draw_list->AddLine(l1_p1, l1_p2, theme().on_primary, MODUI_WIDGET_OUTLINE_WIDTH);
			draw_list->AddLine(l2_p1, l2_p2, theme().on_primary, MODUI_WIDGET_OUTLINE_WIDTH);
		}

		return pos + size;
	}
}