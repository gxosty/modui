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

		Checkbox* set_state(bool state);
		bool get_state();

		virtual Widget* on_release(ButtonInputCallback callback) override;

		virtual Vec2 render(Vec2 pos, Vec2 reserved_space) override;

	private:
		float _rounding;

		bool _state;

		float _press_factor;
		float _state_factor;
	};
}