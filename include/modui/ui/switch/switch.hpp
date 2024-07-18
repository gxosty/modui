#pragma once

#include "../../core/common.hpp"
#include "../button/basebutton.hpp"

namespace modui::ui
{
	class Switch : public BaseButton
	{
	public:
		Switch(bool state);
		static Switch* init(bool state = false);

		Switch* set_state(bool state) override;
		bool get_state();

		Widget* on_release(ButtonInputCallback callback) override;

		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		float calculate_size_x(float reserved_space_x) override;
		float calculate_size_y(float reserved_space_y) override;

	private:
		bool _state;

		float _press_factor;
		float _state_factor;
	};
}