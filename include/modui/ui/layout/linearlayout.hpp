#pragma once

#include "../../core/common.hpp"
#include "../widget.hpp"

namespace modui::ui
{
	class LinearLayout : public Widget
	{
	public:
		LinearLayout(modui::LayoutOrientation orientation);

		static LinearLayout* init(
			modui::LayoutOrientation orientation = LAYOUT_ORIENTATION_VERTICAL
		);

		virtual Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		LinearLayout* set_orientation(modui::LayoutOrientation orientation) override;

		virtual float calculate_size_x(float reserved_space_x) override;
		virtual float calculate_size_y(float reserved_space_y) override;

	private:
		modui::LayoutOrientation _orientation;

		Vec2 _render_vertical(Vec2 pos, Vec2 reserved_space);
		Vec2 _render_horizontal(Vec2 pos, Vec2 reserved_space);
	};
}