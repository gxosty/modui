#include <modui/ui/layout/scrolllayout.hpp>

namespace modui::ui
{
	ScrollLayout::ScrollLayout() : Widget()
	{
		this->_size = Vec2(
			MODUI_SIZE_WIDTH_FULL,
			MODUI_SIZE_HEIGHT_FULL
		);
	}

	ScrollLayout* ScrollLayout::init() { return new ScrollLayout(); }

	ScrollLayout* ScrollLayout::add(Widget* widget)
	{
		if (!this->_children.empty())
			throw exceptions::AddWidgetException("Only one widget can be added to `modui::ui::ScrollLayout` object");

		return (ScrollLayout*)Widget::add(widget);
	}

	Vec2 ScrollLayout::render(Vec2 pos, Vec2 reserved_space)
	{
		if (!this->_children.empty())
		{
			Theme& theme = this->get_theme();

			ImGui::PushID(this->_id);
			ImGui::SetNextWindowPos(pos);

			ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, utils::dp(3));
			ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, FLT_MAX);
			ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, 0);
			ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, theme().secondary);
			ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, theme().secondary);
			ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, theme().secondary);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, 0);
			bool opened = ImGui::BeginChild(DEFAULT_ID, this->_calculated_size, 0,
				  ImGuiWindowFlags_NoTitleBar
				| ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoMove
				| ImGuiWindowFlags_NoCollapse);

			if (opened)
				this->_children[0]->render(ImGui::GetCursorScreenPos(), this->_calculated_size);

			ImGui::EndChild();
			ImGui::PopStyleColor(5);
			ImGui::PopStyleVar(2);
			ImGui::PopID();
		}

		return pos + this->_calculated_size;
	}

	float ScrollLayout::calculate_size_x(float reserved_space_x)
	{
		float x = this->_size.x;

		if (x == MODUI_SIZE_WIDTH_FULL)
		{
			x = reserved_space_x;
			if (!this->_children.empty()) this->_children[0]->calculate_size_x(x);
		}
		else if (x == MODUI_SIZE_WIDTH_WRAP)
		{
			if (!this->_children.empty())
			{
				x = this->_children[0]->calculate_size_x(reserved_space_x);
			}
			else
			{
				x = 0.0f;
			}
		}
		else if (x < 0.0f)
		{
			x = reserved_space_x + x;
			if (!this->_children.empty()) this->_children[0]->calculate_size_x(x);
		}

		this->_calculated_size.x = x;

		return x;
	}

	float ScrollLayout::calculate_size_y(float reserved_space_y)
	{
		float y = this->_size.y;

		if ((y == MODUI_SIZE_WIDTH_FULL) || (y == MODUI_SIZE_HEIGHT_WRAP))
		{
			y = reserved_space_y;
		}
		else if (y < 0.0f)
		{
			y = reserved_space_y + y;
		}

		if (!this->_children.empty()) this->_children[0]->calculate_size_y(99999.0f);

		this->_calculated_size.y = y;

		return y;
	}
}