#include "divider.hpp"

namespace modui::ui
{
	Divider::Divider(Type type) : Widget(),
		_type{type}
	{
		this->_size = {MODUI_SIZE_WIDTH_FULL, utils::dp(1)};
	}

	Divider* Divider::init(Type type) { return new Divider(type); }

	Vec2 Divider::render(Vec2 pos, Vec2 reserved_space)
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		Theme& theme = this->get_theme();

		Vec2 size = this->_calculated_size;
		this->_pos = pos;

		switch (this->_type)
		{
		case Type::FULL:
			draw_list->AddLine(pos, Vec2(pos.x + size.x, pos.y), theme().outline_variant, utils::dp(1));
			break;
		case Type::INSENT:
			draw_list->AddLine(Vec2(pos.x + utils::dp(16), pos.y), Vec2(pos.x + size.x - utils::dp(16), pos.y), theme().outline_variant, utils::dp(1));
			break;
		}

		return pos + size;
	}
}