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

		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		float calculate_size_x(float reserved_space_x) override;
		float calculate_size_y(float reserved_space_y) override;

	private:
		float _press_factor;
	};
}