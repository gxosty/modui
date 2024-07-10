#pragma once

#include "../../core/common.hpp"
#include "../button/basebutton.hpp"

namespace modui::ui
{
	class Checkbox : public BaseButton
	{
	public:
		Checkbox(bool state);
		static Checkbox* init(bool state = false);

		Checkbox* set_state(bool state) override;
		bool get_state();

		virtual Widget* on_release(ButtonInputCallback callback) override;

		virtual Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		virtual float calculate_size_x(float reserved_space_x) override;
		virtual float calculate_size_y(float reserved_space_y) override;

	private:
		float _rounding;

		bool _state;

		float _press_factor;
	};
}