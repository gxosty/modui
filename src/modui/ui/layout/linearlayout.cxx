#include <modui/ui/layout/linearlayout.hpp>

namespace modui::ui
{
	LinearLayout::LinearLayout(modui::LayoutOrientation orientation) : Widget(),
		_orientation{orientation}
	{
		this->_size = Vec2(
			MODUI_SIZE_WIDTH_FULL,
			MODUI_SIZE_HEIGHT_FULL
		);
	};

	LinearLayout* LinearLayout::init(modui::LayoutOrientation orientation) { return new LinearLayout(orientation); }

	LinearLayout* LinearLayout::set_orientation(modui::LayoutOrientation orientation)
	{
		this->_orientation = orientation;

		return this;
	}

	Vec2 LinearLayout::render(Vec2 pos, Vec2 reserved_space)
	{
		if (this->_children.empty()) return pos;

		this->_pos = pos;
		Vec2 size = this->_size;

		if (size.x <= 0.0f) size.x = reserved_space.x;
		if (size.y <= 0.0f) size.y = reserved_space.y;

		return this->_orientation == LAYOUT_ORIENTATION_VERTICAL ?
			this->_render_vertical(pos, reserved_space) :
			this->_render_horizontal(pos, reserved_space);
	}

	Vec2 LinearLayout::_render_vertical(Vec2 pos, Vec2 reserved_space)
	{
		pos.x += this->_padding.w;
		pos.y += this->_padding.x;
		reserved_space.x -= this->_padding.y;
		reserved_space.x -= this->_padding.w;
		reserved_space.y -= this->_padding.x;
		reserved_space.y -= this->_padding.z;
		Vec2 max_pos = pos;

		bool first_done = false;
		Vec2 widget_pos;
		Vec2 widget_space;
		Vec2 widget_end;
		int idx = this->_children.size();
		const float xbkp = pos.x;

		for (auto& widget : this->_children)
		{
			if (first_done)
			{
				reserved_space.y -= widget_end.y - widget_pos.y + this->_spacing.y;

				pos.x = xbkp;
				pos.y = widget_end.y + this->_spacing.y;
			}

			first_done = true;

			widget_pos = pos;
			widget_space.x = reserved_space.x;
			widget_space.y = (reserved_space.y - this->_spacing.y * (idx - 1)) / idx;
			idx--;

			widget_end = widget->render(widget_pos, widget_space);

			if (widget_end.x > max_pos.x) max_pos.x = widget_end.x;
			if (widget_end.y > max_pos.y) max_pos.y = widget_end.y;
		}

		return max_pos + Vec2(this->_padding.y, this->_padding.z);
	}

	Vec2 LinearLayout::_render_horizontal(Vec2 pos, Vec2 reserved_space)
	{
		pos.x += this->_padding.w;
		pos.y += this->_padding.x;
		reserved_space.x -= this->_padding.y;
		reserved_space.x -= this->_padding.w;
		reserved_space.y -= this->_padding.x;
		reserved_space.y -= this->_padding.z;
		Vec2 max_pos = pos;

		bool first_done = false;
		Vec2 widget_pos;
		Vec2 widget_space;
		Vec2 widget_end;
		int idx = this->_children.size();
		const float ybkp = pos.y;

		for (auto& widget : this->_children)
		{
			if (first_done)
			{
				reserved_space.x -= widget_end.x - widget_pos.x + this->_spacing.x;

				pos.x = widget_end.x + this->_spacing.x;
				pos.y = ybkp;
			}

			first_done = true;

			widget_pos = pos;
			widget_space.x = (reserved_space.x - this->_spacing.x * (idx - 1)) / idx;
			widget_space.y = reserved_space.y;
			idx--;

			widget_end = widget->render(widget_pos, widget_space);

			if (widget_end.x > max_pos.x) max_pos.x = widget_end.x;
			if (widget_end.y > max_pos.y) max_pos.y = widget_end.y;
		}

		return max_pos + Vec2(this->_padding.y, this->_padding.z);
	}
}