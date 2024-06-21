#pragma once

#include "../../core/common.hpp"
#include "baseslider.hpp"

namespace modui::ui
{
	class Slider : public BaseSlider
	{
	public:
		Slider(float min_value, float max_value);
		static Slider* init(float min_value, float max_value);

		virtual Vec2 render(Vec2 pos, Vec2 reserved_space) override;

	private:
		float _press_factor;
	};
}