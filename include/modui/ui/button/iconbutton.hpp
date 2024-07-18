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
		IconButton* set_icon_size(float icon_size) override;
		IconButton* set_state(bool state) override;

		const ImageID get_icon();
		bool get_state();

		IconButton* on_release(ButtonInputCallback callback) override;

		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		float calculate_size_x(float reserved_space_x) override;
		float calculate_size_y(float reserved_space_y) override;

	private:
		ImageID _icon;
		float _icon_size;
		float _rounding;
		bool _state;
		bool _toggleable;

		float _press_factor;
	};

	class FilledIconButton : public BaseButton
	{
	public:
		FilledIconButton(ImageID icon);
		static FilledIconButton* init(ImageID icon = nullptr);

		FilledIconButton* set_icon(ImageID icon) override;
		FilledIconButton* set_icon_size(float icon_size) override;
		FilledIconButton* set_state(bool state) override;

		const ImageID get_icon();
		bool get_state();

		FilledIconButton* on_release(ButtonInputCallback callback) override;

		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		float calculate_size_x(float reserved_space_x) override;
		float calculate_size_y(float reserved_space_y) override;

	private:
		ImageID _icon;
		float _icon_size;
		float _rounding;
		bool _state;
		bool _toggleable;

		float _press_factor;
	};

	class FilledTonalIconButton : public BaseButton
	{
	public:
		FilledTonalIconButton(ImageID icon);
		static FilledTonalIconButton* init(ImageID icon = nullptr);

		FilledTonalIconButton* set_icon(ImageID icon) override;
		FilledTonalIconButton* set_icon_size(float icon_size) override;
		FilledTonalIconButton* set_state(bool state) override;

		const ImageID get_icon();
		bool get_state();

		FilledTonalIconButton* on_release(ButtonInputCallback callback) override;

		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		float calculate_size_x(float reserved_space_x) override;
		float calculate_size_y(float reserved_space_y) override;

	private:
		ImageID _icon;
		float _icon_size;
		float _rounding;
		bool _state;
		bool _toggleable;

		float _press_factor;
	};

	class OutlinedIconButton : public BaseButton
	{
	public:
		OutlinedIconButton(ImageID icon);
		static OutlinedIconButton* init(ImageID icon = nullptr);

		OutlinedIconButton* set_icon(ImageID icon) override;
		OutlinedIconButton* set_icon_size(float icon_size) override;
		OutlinedIconButton* set_state(bool state) override;

		const ImageID get_icon();
		bool get_state();

		OutlinedIconButton* on_release(ButtonInputCallback callback) override;

		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		float calculate_size_x(float reserved_space_x) override;
		float calculate_size_y(float reserved_space_y) override;

	private:
		ImageID _icon;
		float _icon_size;
		float _rounding;
		bool _state;
		bool _toggleable;

		float _press_factor;
	};
}