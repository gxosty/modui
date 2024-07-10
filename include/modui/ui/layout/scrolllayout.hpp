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

		virtual ScrollLayout* add(Widget* widget) override;

		virtual Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		virtual float calculate_size_x(float reserved_space_x) override;
		virtual float calculate_size_y(float reserved_space_y) override;
	};
}