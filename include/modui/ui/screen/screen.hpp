#pragma once

#include "../../core/common.hpp"
#include "../widget.hpp"

#include <string>

namespace modui::ui
{
	class Screen : public Widget
	{
	public:
		Screen(const std::string& name);
		static Screen* init(const std::string& name = "");

		Screen* set_name(const std::string& name);
		const std::string& get_name();

		virtual Screen* add_widget(Widget* widget) override;
		virtual Vec2 render(Vec2 pos, Vec2 reserved_space) override;

	private:
		std::string _name;

	};
}