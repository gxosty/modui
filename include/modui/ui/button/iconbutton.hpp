#pragma once

#include "../../core/common.hpp"
#include "../../core/image/image.hpp"
#include "basebutton.hpp"

namespace modui::ui
{
	class IconButton : public BaseButton
	{
	public:
		IconButton(ImageID icon);
		static IconButton* init(ImageID icon = nullptr);

		IconButton* set_icon(ImageID icon) override;
		const ImageID get_icon();

		IconButton* set_icon_size(float icon_size) override;

		virtual Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		virtual float calculate_size_x(float reserved_space_x) override;
		virtual float calculate_size_y(float reserved_space_y) override;

	private:
		ImageID _icon;
		float _icon_size;
		float _rounding;

		float _press_factor;
	};
}