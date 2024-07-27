#include <modui/ui/button/basebutton.hpp>
#include <modui/app.hpp>

namespace modui::ui
{
	BaseButton::BaseButton() : Widget(),
		_on_press_callback{MODUI_EMPTY_CALLBACK},
		_on_hold_callback{MODUI_EMPTY_CALLBACK},
		_on_release_callback{MODUI_EMPTY_CALLBACK},
		_is_pressed{false},
		_is_released{false} {}

	Widget* BaseButton::on_press(ButtonInputCallback callback)
	{
		this->_on_press_callback = callback;

		return this;
	}

	Widget* BaseButton::on_hold(ButtonInputCallback callback)
	{
		this->_on_hold_callback = callback;

		return this;
	}

	Widget* BaseButton::on_release(ButtonInputCallback callback)
	{
		this->_on_release_callback = callback;

		return this;
	}

	void BaseButton::on_press_call()
	{
		modui::get_current_app()->add_callback_to_queue(this, &this->_on_press_callback);
	}

	void BaseButton::on_hold_call()
	{
		modui::get_current_app()->add_callback_to_queue(this, &this->_on_hold_callback);
	}

	void BaseButton::on_release_call()
	{
		modui::get_current_app()->add_callback_to_queue(this, &this->_on_release_callback);
	}

	Vec2 BaseButton::render(Vec2 pos, Vec2 reserved_space)
	{
		ImGui::PushID(this->_id);
		ImGui::SetCursorScreenPos(pos);
		this->_is_released = ImGui::InvisibleButton(DEFAULT_ID, reserved_space);
		ImGui::PopID();
		this->_is_held = ImGui::IsItemActive();
		this->_is_pressed = ImGui::IsItemActivated();

		if (this->_is_pressed) this->on_press_call();
		if (this->_is_held) this->on_hold_call();
		if (this->_is_released) this->on_release_call();

		return {0.0f, 0.0f};
	}
}