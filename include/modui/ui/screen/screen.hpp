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

		Screen* set_name(const std::string& name) override;
		const std::string& get_name();

		Screen* add(Widget* widget) override;
		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		float calculate_size_x(float reserved_space_x) override;
		float calculate_size_y(float reserved_space_y) override;

	private:
		std::string _name;

	};
}