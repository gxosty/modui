#pragma once

#include "../../core/common.hpp"
#include "../widget.hpp"

namespace modui::ui
{
	class ScrollLayout : public Widget
	{
	public:
		ScrollLayout();

		static ScrollLayout* init();

		ScrollLayout* add(Widget* widget) override;

		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		float calculate_size_x(float reserved_space_x) override;
		float calculate_size_y(float reserved_space_y) override;
	};
}