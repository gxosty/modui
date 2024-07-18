#pragma once

#include "../../core/common.hpp"
#include "../layout/linearlayout.hpp"

namespace modui::ui
{
	class FilledCard : public LinearLayout
	{
	public:
		FilledCard(modui::LayoutOrientation orientation);

		static FilledCard* init(
			modui::LayoutOrientation orientation = LAYOUT_ORIENTATION_VERTICAL
		);

		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

	private:
		float _rounding;
	};
}