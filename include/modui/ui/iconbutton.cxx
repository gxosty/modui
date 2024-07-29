#include <modui/ui/iconbutton.hpp>
#include <modui/core/image/selectableimage.hpp>

namespace modui::ui
{
	IconButton::IconButton(ImageID icon) : BaseButton(),
		_icon{icon},
		_icon_size{utils::dp(24)},
		_press_factor{0.0f},
		_state{false},
		_toggleable{false}
	{
		this->_size = Vec2(utils::dp(40), utils::dp(40));
		this->_rounding = this->_size.y / 2.0f;
		BaseButton::on_release(MODUI_CALLBACK(this) {
			if (this->_toggleable)
				this->set_state(!this->get_state());
		});
	}

	IconButton* IconButton::init(ImageID icon) { return new IconButton(icon); }

	IconButton* IconButton::set_icon(ImageID icon) { this->_icon = icon; return this; }

	const ImageID IconButton::get_icon() { return this->_icon; }

	IconButton* IconButton::set_icon_size(float icon_size) { this->_icon_size = icon_size; return this; }

	IconButton* IconButton::set_state(bool state)
	{
		this->_state = state;
		return this;
	}

	IconButton* IconButton::set_toggleable(bool toggleable)
	{
		this->_toggleable = toggleable;
		return this;
	}

	bool IconButton::get_state() { return this->_state; }

	IconButton* IconButton::on_release(ButtonInputCallback callback)
	{
		BaseButton::on_release(MODUI_CALLBACK(this, callback) {
			if (this->_toggleable)
				this->set_state(!this->get_state());
			callback(this);
		});

		return this;
	}

	Vec2 IconButton::render(Vec2 pos, Vec2 reserved_space)
	{
		ImDrawList* draw_list =  ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		Vec2 size = this->_calculated_size;
		this->_pos = pos;

		ui::BaseButton::render(pos, size);

		this->_press_factor = utils::clamp(
			this->_press_factor + (ImGui::GetIO().DeltaTime * MODUI_WIDGET_PRESS_TRANSITION_SPEED) * (this->_is_held ? 1.0f : -1.0f),
			0.0f,
			1.0f
		);

		Col32 col1;
		Col32 col2;

		if (this->_state)
		{
			col1 = theme().primary;
		}
		else
		{
			col1 = theme().on_surface_variant;
		}

		Col32 ripple_color = (col1 & 0xFFFFFF) | (unsigned(0xFF * this->_press_factor * 0.1f) << 24);

		draw_list->AddRectFilled(
			pos,
			pos + size,
			ripple_color,
			this->_rounding
		);

		Vec2 icon_size = Vec2(this->_icon_size, this->_icon_size);
		Vec2 icon_pos = pos + (size - icon_size) / 2.0f;

		if (this->_icon != nullptr)
		{
			if (this->_icon->get_image_type() == modui::image::ImageType::SELECTABLE)
				reinterpret_cast<modui::image::SelectableImage*>(this->_icon)->set_selected(this->_state);

			this->_icon->draw(icon_pos, icon_size, col1);
		}

		return pos + size;
	}

	float IconButton::calculate_size_x(float reserved_space_x)
	{
		float x = this->_size.x;

		if (x == MODUI_SIZE_WIDTH_FULL)
		{
			x = reserved_space_x;
		}
		else if (x == MODUI_SIZE_WIDTH_WRAP)
		{
			x = utils::dp(40);
		}
		else if (x < 0.0f)
		{
			x = reserved_space_x + x;
		}

		this->_calculated_size.x = x;

		return x;
	}

	float IconButton::calculate_size_y(float reserved_space_y)
	{
		float y = this->_size.y;

		if (y == MODUI_SIZE_WIDTH_FULL)
		{
			y = reserved_space_y;
		}
		else if (y == MODUI_SIZE_HEIGHT_WRAP)
		{
			y = utils::dp(40);
		}
		else if (y < 0.0f)
		{
			y = reserved_space_y + y;
		}

		this->_calculated_size.y = y;

		return y;
	}





	FilledIconButton::FilledIconButton(ImageID icon) : IconButton(icon)
	{
		this->set_state(true);
	}

	FilledIconButton* FilledIconButton::init(ImageID icon) { return new FilledIconButton(icon); }

	Vec2 FilledIconButton::render(Vec2 pos, Vec2 reserved_space)
	{
		ImDrawList* draw_list =  ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		Vec2 size = this->_calculated_size;
		this->_pos = pos;

		ui::BaseButton::render(pos, size);

		this->_press_factor = utils::clamp(
			this->_press_factor + (ImGui::GetIO().DeltaTime * MODUI_WIDGET_PRESS_TRANSITION_SPEED) * (this->_is_held ? 1.0f : -1.0f),
			0.0f,
			1.0f
		);

		Col32 col1;
		Col32 col2;

		if (this->_state)
		{
			col1 = theme().primary;
			col2 = theme().on_primary;
		}
		else
		{
			col1 = theme().surface_container_highest;
			col2 = theme().primary;
		}

		Col32 fill_color = col1;
		Col32 ripple_color = (col2 & 0xFFFFFF) | (unsigned(0xFF * this->_press_factor * 0.1f) << 24);

		draw_list->AddRectFilled(
			pos,
			pos + size,
			fill_color,
			this->_rounding
		);

		draw_list->AddRectFilled(
			pos,
			pos + size,
			ripple_color,
			this->_rounding
		);

		Vec2 icon_size = Vec2(this->_icon_size, this->_icon_size);
		Vec2 icon_pos = pos + (size - icon_size) / 2.0f;

		if (this->_icon != nullptr)
		{
			if (this->_icon->get_image_type() == modui::image::ImageType::SELECTABLE)
				reinterpret_cast<modui::image::SelectableImage*>(this->_icon)->set_selected(this->_state);

			this->_icon->draw(icon_pos, icon_size, col2);
		}

		return pos + size;
	}



	FilledTonalIconButton::FilledTonalIconButton(ImageID icon) : IconButton(icon)
	{
		this->set_state(false);
	}

	FilledTonalIconButton* FilledTonalIconButton::init(ImageID icon) { return new FilledTonalIconButton(icon); }

	Vec2 FilledTonalIconButton::render(Vec2 pos, Vec2 reserved_space)
	{
		ImDrawList* draw_list =  ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		Vec2 size = this->_calculated_size;
		this->_pos = pos;

		ui::BaseButton::render(pos, size);

		this->_press_factor = utils::clamp(
			this->_press_factor + (ImGui::GetIO().DeltaTime * MODUI_WIDGET_PRESS_TRANSITION_SPEED) * (this->_is_held ? 1.0f : -1.0f),
			0.0f,
			1.0f
		);

		Col32 col1;
		Col32 col2;

		if (this->_state)
		{
			col1 = theme().secondary_container;
			col2 = theme().on_secondary_container;
		}
		else
		{
			col1 = theme().surface_container_highest;
			col2 = theme().on_surface_variant;
		}

		Col32 fill_color = col1;
		Col32 ripple_color = (col2 & 0xFFFFFF) | (unsigned(0xFF * this->_press_factor * 0.1f) << 24);

		draw_list->AddRectFilled(
			pos,
			pos + size,
			fill_color,
			this->_rounding
		);

		draw_list->AddRectFilled(
			pos,
			pos + size,
			ripple_color,
			this->_rounding
		);

		Vec2 icon_size = Vec2(this->_icon_size, this->_icon_size);
		Vec2 icon_pos = pos + (size - icon_size) / 2.0f;

		if (this->_icon != nullptr)
		{
			if (this->_icon->get_image_type() == modui::image::ImageType::SELECTABLE)
				reinterpret_cast<modui::image::SelectableImage*>(this->_icon)->set_selected(this->_state);

			this->_icon->draw(icon_pos, icon_size, col2);
		}

		return pos + size;
	}



	OutlinedIconButton::OutlinedIconButton(ImageID icon) : IconButton(icon)
	{
		this->set_state(false);
	}

	OutlinedIconButton* OutlinedIconButton::init(ImageID icon) { return new OutlinedIconButton(icon); }

	Vec2 OutlinedIconButton::render(Vec2 pos, Vec2 reserved_space)
	{
		ImDrawList* draw_list =  ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		Vec2 size = this->_calculated_size;
		this->_pos = pos;

		ui::BaseButton::render(pos, size);

		this->_press_factor = utils::clamp(
			this->_press_factor + (ImGui::GetIO().DeltaTime * MODUI_WIDGET_PRESS_TRANSITION_SPEED) * (this->_is_held ? 1.0f : -1.0f),
			0.0f,
			1.0f
		);

		Col32 col1;
		Col32 col2;
		Col32 col3;

		if (this->_state)
		{
			col1 = theme().inverse_surface;
			col2 = theme().inverse_on_surface;
			col3 = 0x0;
		}
		else
		{
			col1 = 0x0;
			col2 = theme().on_surface_variant;
			col3 = theme().outline;
		}

		Col32 fill_color = col1;
		Col32 ripple_color = (col2 & 0xFFFFFF) | (unsigned(0xFF * this->_press_factor * 0.1f) << 24);
		Col32 outline_color = col3;

		draw_list->AddRectFilled(
			pos,
			pos + size,
			fill_color,
			this->_rounding
		);

		draw_list->AddRect(
			pos,
			pos + size,
			outline_color,
			this->_rounding,
			utils::dp(1)
		);

		draw_list->AddRectFilled(
			pos,
			pos + size,
			ripple_color,
			this->_rounding
		);

		Vec2 icon_size = Vec2(this->_icon_size, this->_icon_size);
		Vec2 icon_pos = pos + (size - icon_size) / 2.0f;

		if (this->_icon != nullptr)
		{
			if (this->_icon->get_image_type() == modui::image::ImageType::SELECTABLE)
				reinterpret_cast<modui::image::SelectableImage*>(this->_icon)->set_selected(this->_state);

			this->_icon->draw(icon_pos, icon_size, col2);
		}

		return pos + size;
	}
}