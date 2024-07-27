#include <modui/ui/layout/linearlayout.hpp>

namespace modui::ui
{
	LinearLayout::LinearLayout(modui::LayoutOrientation orientation) : Widget(),
		_orientation{orientation}
	{
		this->_size = Vec2(
			MODUI_SIZE_WIDTH_FULL,
			MODUI_SIZE_HEIGHT_WRAP
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
		// if (this->_children.empty()) return pos;

		this->_pos = pos;

		Vec2 ret_pos = this->_orientation == LAYOUT_ORIENTATION_VERTICAL ?
			this->_render_vertical(pos, reserved_space) :
			this->_render_horizontal(pos, reserved_space);

		ImGui::SetCursorScreenPos(pos);
		ImGui::Dummy(ret_pos - pos);

		return ret_pos;
	}

	Vec2 LinearLayout::_render_vertical(Vec2 pos, Vec2 reserved_space)
	{
		Vec2 in_pos = Vec2(pos.x + this->_padding.w, pos.y + this->_padding.x);

		Vec2 size = this->_size;
		bool adaptive_width = (size.x == 0.0f);
		bool adaptive_height = (size.y == 0.0f);

		if (size.x <= 0.0f)
		{
			size.x = reserved_space.x + (size.x == MODUI_SIZE_WIDTH_FULL ? 0.0f : size.x);
		}

		if (size.y <= 0.0f)
		{
			size.y = reserved_space.y + (size.y == MODUI_SIZE_WIDTH_FULL ? 0.0f : size.y);
		}

		Vec2 in_size = size;
		in_size.x -= this->_padding.y;
		in_size.x -= this->_padding.w;
		in_size.y -= this->_padding.x;
		in_size.y -= this->_padding.z;

		Vec2 max_pos = in_pos;

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		// draw_list->PushClipRect(pos, pos + size);
		// draw_list->AddRect(pos, pos + size, 0xFF7F7F7F, 3.0f);
		// draw_list->AddRectFilled(in_pos, in_pos + in_size, 0xFF00FF00);

		bool first_done = false;
		Vec2 widget_pos;
		Vec2 widget_space;
		Vec2 widget_end;
		int idx = this->_children.size();
		const float xbkp = in_pos.x;

		Vec2 widget_reserved_space = in_size;
		Vec2 widget_in_pos = in_pos;

		for (auto& widget : this->_children)
		{
			if (first_done)
			{
				widget_reserved_space.y -= widget_end.y - widget_pos.y + this->_spacing.y;

				widget_in_pos.x = xbkp;
				widget_in_pos.y = widget_end.y + this->_spacing.y;
			}

			first_done = true;

			widget_pos = widget_in_pos;
			widget_space.x = widget_reserved_space.x;
			widget_space.y = (widget_reserved_space.y - this->_spacing.y * (idx - 1)) / idx;
			idx--;

			widget_end = widget->render(widget_pos, widget_space);

			if (widget_end.x > max_pos.x) max_pos.x = widget_end.x;
			if (widget_end.y > max_pos.y) max_pos.y = widget_end.y;
		}

		// draw_list->PopClipRect();

		max_pos = max_pos + Vec2(this->_padding.y, this->_padding.z);

		if (!adaptive_width)
		{
			max_pos.x = pos.x + size.x;
		}

		// if (!adaptive_height)
		// {
		// 	max_pos.y = pos.y + size.y;
		// }

		// draw_list->AddRect(pos, max_pos, 0xFF00FFFF);

		return max_pos;
	}

	Vec2 LinearLayout::_render_horizontal(Vec2 pos, Vec2 reserved_space)
	{
		Vec2 in_pos = Vec2(pos.x + this->_padding.w, pos.y + this->_padding.x);

		Vec2 size = this->_size;
		bool adaptive_width = (size.x == 0.0f);
		bool adaptive_height = (size.y == 0.0f);

		if (size.x <= 0.0f)
		{
			size.x = reserved_space.x + (size.x == MODUI_SIZE_WIDTH_FULL ? 0.0f : size.x);
		}

		if (size.y <= 0.0f)
		{
			size.y = reserved_space.y + (size.y == MODUI_SIZE_WIDTH_FULL ? 0.0f : size.y);
		}

		Vec2 in_size = size;
		in_size.x -= this->_padding.y;
		in_size.x -= this->_padding.w;
		in_size.y -= this->_padding.x;
		in_size.y -= this->_padding.z;

		Vec2 max_pos = in_pos;

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		// draw_list->PushClipRect(pos, pos + size);
		// draw_list->AddRect(pos, pos + size, 0xFF7F7F7F, 3.0f);
		// draw_list->AddRectFilled(in_pos, in_pos + in_size, 0xFFFFFF00);

		bool first_done = false;
		Vec2 widget_pos;
		Vec2 widget_space;
		Vec2 widget_end;
		int idx = this->_children.size();
		const float ybkp = in_pos.y;

		Vec2 widget_reserved_space = in_size;
		Vec2 widget_in_pos = in_pos;

		for (auto& widget : this->_children)
		{
			if (first_done)
			{
				widget_reserved_space.x -= widget_end.x - widget_pos.x + this->_spacing.x;

				widget_in_pos.x = widget_end.x + this->_spacing.x;
				widget_in_pos.y = ybkp;
			}

			first_done = true;

			widget_pos = widget_in_pos;
			widget_space.x = (widget_reserved_space.x - this->_spacing.x * (idx - 1)) / idx;
			widget_space.y = widget_reserved_space.y;
			idx--;

			widget_end = widget->render(widget_pos, widget_space);

			if (widget_end.x > max_pos.x) max_pos.x = widget_end.x;
			if (widget_end.y > max_pos.y) max_pos.y = widget_end.y;
		}

		// draw_list->PopClipRect();

		max_pos = max_pos + Vec2(this->_padding.y, this->_padding.z);

		// if (!adaptive_width)
		// {
		// 	max_pos.x = pos.x + size.x;
		// }

		if (!adaptive_height)
		{
			max_pos.y = pos.y + size.y;
		}

		// draw_list->AddRect(pos, max_pos, 0xFF00FFFF);

		return max_pos;
	}

	float LinearLayout::calculate_size_x(float reserved_space_x)
	{
		float x = this->_size.x;

		float calculated_x = x;

		if ((x == MODUI_SIZE_WIDTH_FULL) || (x == MODUI_SIZE_WIDTH_WRAP))
		{
			calculated_x = reserved_space_x;
		}
		else if (x < 0.0f)
		{
			calculated_x = reserved_space_x + x;
		}

		float inner_reserved_space_x = calculated_x - this->_padding.y - this->_padding.w;

		if (this->_orientation == modui::LAYOUT_ORIENTATION_HORIZONTAL)
		{
			unsigned children_count = this->_children.size();
			inner_reserved_space_x -= this->_spacing.x * (children_count - 1);
			unsigned fwidth_count = 0;
			float max_x = 0.0f;

			for (auto child : this->_children)
			{
				if (child->get_size().x == MODUI_SIZE_WIDTH_FULL)
				{
					fwidth_count++;
					continue;
				}

				float _x = child->calculate_size_x(inner_reserved_space_x);
				max_x += _x;
				inner_reserved_space_x -= _x;
			}

			if (fwidth_count)
			{
				float freserved_space_x = inner_reserved_space_x / fwidth_count;

				for (auto child : this->_children)
				{
					if (child->get_size().x != MODUI_SIZE_WIDTH_FULL) continue;

					child->calculate_size_x(freserved_space_x);
				}

			}
			else
			{
				if (x == MODUI_SIZE_WIDTH_WRAP)
				{
					calculated_x = max_x + this->_padding.y + this->_padding.w + this->_spacing.x * (children_count - 1);
				}
			}

		}
		else
		{
			unsigned fwidth_count = 0;
			float max_x = 0.0f;

			for (auto child : this->_children)
			{
				if ((x == MODUI_SIZE_WIDTH_WRAP) && (child->get_size().x == MODUI_SIZE_WIDTH_FULL))
				{
					fwidth_count++;
					continue;
				}

				max_x = fmax(child->calculate_size_x(inner_reserved_space_x), max_x);
			}

			if (fwidth_count)
			{

				for (auto child : this->_children)
				{
					if (child->get_size().x != MODUI_SIZE_WIDTH_FULL) continue;

					child->calculate_size_x(max_x);
				}

			}

			if (x == MODUI_SIZE_WIDTH_WRAP)
			{
				calculated_x = max_x + this->_padding.y + this->_padding.w;
			}

		}

		x = calculated_x;
		this->_calculated_size.x = x;

		return x;
	}

	float LinearLayout::calculate_size_y(float reserved_space_y)
	{
		float y = this->_size.y;

		float calculated_y = y;

		if ((y == MODUI_SIZE_HEIGHT_FULL) || (y == MODUI_SIZE_HEIGHT_WRAP))
		{
			calculated_y = reserved_space_y;
		}
		else if (y < 0.0f)
		{
			calculated_y = reserved_space_y + y;
		}

		float inner_reserved_space_y = calculated_y - this->_padding.y - this->_padding.w;

		if (this->_orientation == modui::LAYOUT_ORIENTATION_VERTICAL)
		{
			unsigned children_count = this->_children.size();
			inner_reserved_space_y -= this->_spacing.y * (children_count - 1);
			unsigned fheight_count = 0;
			float max_y = 0.0f;

			for (auto child : this->_children)
			{
				if (child->get_size().y == MODUI_SIZE_HEIGHT_FULL)
				{
					fheight_count++;
					continue;
				}

				float _y = child->calculate_size_y(inner_reserved_space_y);
				max_y += _y;
				inner_reserved_space_y -= _y;
			}

			if (fheight_count)
			{
				float freserved_space_y = inner_reserved_space_y / fheight_count;

				for (auto child : this->_children)
				{
					if (child->get_size().y != MODUI_SIZE_HEIGHT_FULL) continue;

					child->calculate_size_y(freserved_space_y);
				}

			}
			else
			{
				if (y == MODUI_SIZE_HEIGHT_WRAP)
				{
					calculated_y = max_y + this->_padding.x + this->_padding.z + this->_spacing.x * (children_count - 1);
				}
			}

		}
		else
		{
			unsigned fheight_count = 0;
			float max_y = 0.0f;

			for (auto child : this->_children)
			{
				if ((y == MODUI_SIZE_HEIGHT_WRAP) && (child->get_size().y == MODUI_SIZE_HEIGHT_FULL))
				{
					fheight_count++;
					continue;
				}

				max_y = fmax(child->calculate_size_y(inner_reserved_space_y), max_y);
			}

			if (fheight_count)
			{
				for (auto child : this->_children)
				{
					if (child->get_size().y != MODUI_SIZE_HEIGHT_FULL) continue;

					child->calculate_size_y(max_y);
				}

			}

			if (y == MODUI_SIZE_HEIGHT_WRAP)
			{
				calculated_y = max_y + this->_padding.x + this->_padding.z;
			}
		}

		y = calculated_y;
		this->_calculated_size.y = y;

		return y;
	}
}