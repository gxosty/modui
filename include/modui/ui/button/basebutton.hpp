#pragma once

#include "../../core/common.hpp"
#include "../widget.hpp"

namespace modui::ui
{
	class BaseButton : public Widget
	{
	public:
		BaseButton();

		// virtual BaseButton* add_widget(Widget* widget) = 0;
		// virtual BaseButton* remove_widget(Widget* widget) = 0;

		virtual Widget* on_press(ButtonInputCallback callback) override;
		virtual Widget* on_hold(ButtonInputCallback callback) override;
		virtual Widget* on_release(ButtonInputCallback callback) override;

		virtual Vec2 render(Vec2 pos, Vec2 reserved_space) override;

	private:
		ButtonInputCallback _on_press_callback;
		ButtonInputCallback _on_hold_callback;
		ButtonInputCallback _on_release_callback;

	protected:
		bool _is_pressed;
		bool _is_held;
		bool _is_released;

		virtual void on_press_call();
		virtual void on_hold_call();
		virtual void on_release_call();
	};
}