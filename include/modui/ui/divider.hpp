#pragma once

#include "../core/common.hpp"
#include "widget.hpp"

namespace modui::ui
{
	class Divider : public Widget
	{
	public:
		enum class Type {
			FULL = 0,
			INSENT
		};

	public:
		Divider(Type type);

		static Divider* init(Type type = Type::FULL);

		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

	private:
		Type _type;

	};
}