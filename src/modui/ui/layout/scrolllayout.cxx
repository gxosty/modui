#include <modui/ui/layout/scrolllayout.hpp>

namespace modui::ui
{
	ScrollLayout::ScrollLayout() : Widget()
	{
		this->_size = Vec2(0.0f, 0.0f);
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
			bool opened = ImGui::BeginChild(DEFAULT_ID, reserved_space, 0,
				  ImGuiWindowFlags_NoTitleBar
				| ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoMove
				| ImGuiWindowFlags_NoCollapse);

			if (opened)
				this->_children[0]->render(ImGui::GetCursorScreenPos(), reserved_space);

			ImGui::EndChild();
			ImGui::PopStyleColor(4);
			ImGui::PopStyleVar(2);
			ImGui::PopID();
		}

		return pos + reserved_space;
	}
}