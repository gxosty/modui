#include <modui/ui/card/card.hpp>
#include <modui/app.hpp>

namespace modui::ui
{
	FilledCard::FilledCard(modui::LayoutOrientation orientation) : LinearLayout(orientation),
		_rounding{utils::dp(6)} {}

	FilledCard* FilledCard::init(modui::LayoutOrientation orientation) { return new FilledCard(orientation); }

	Vec2 FilledCard::render(Vec2 pos, Vec2 reserved_space)
	{
		ImDrawList* draw_list =  ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();
		ImDrawListSplitter& draw_list_splitter = modui::get_current_app()->get_draw_list_splitter();

		draw_list_splitter.Split(draw_list, 2);
		draw_list_splitter.SetCurrentChannel(draw_list, 1);
		auto ret = LinearLayout::render(pos, reserved_space);

		draw_list_splitter.SetCurrentChannel(draw_list, 0);

		draw_list->AddRectFilled(
			pos,
			ret,
			theme().surface_container_highest,
			this->_rounding
		);

		draw_list_splitter.Merge(draw_list);

		return ret;
	}
}