#pragma once

#include "../core/common.hpp"
#include "basebutton.hpp"

namespace modui::ui
{
	class BaseSlider : public BaseButton
	{
	public:
		BaseSlider(float min_value, float max_value);

		Widget* set_value(float value) override;
		float get_value();

		Widget* on_slide(ButtonInputCallback callback) override;

		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

	private:
		ButtonInputCallback _on_slide_callback;

	protected:
		bool _is_sliding;
		float _min_value;
		float _max_value;
		float _value;

		virtual void on_slide_call();
	};
}