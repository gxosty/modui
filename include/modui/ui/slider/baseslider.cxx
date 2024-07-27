#include <modui/ui/slider/baseslider.hpp>
#include <modui/app.hpp>

#include <iostream>

namespace modui::ui
{
	BaseSlider::BaseSlider(float min_value, float max_value) : BaseButton(),
		_on_slide_callback{MODUI_EMPTY_CALLBACK},
		_min_value{min_value},
		_max_value{max_value} {}

	Widget* BaseSlider::set_value(float value)
	{
		this->_value = value;

		return this;
	}

	float BaseSlider::get_value() { return this->_value; }

	Widget* BaseSlider::on_slide(ButtonInputCallback callback)
	{
		this->_on_slide_callback = callback;

		return this;
	}

	void BaseSlider::on_slide_call()
	{
		modui::get_current_app()->add_callback_to_queue(this, &this->_on_slide_callback);
	}

	Vec2 BaseSlider::render(Vec2 pos, Vec2 reserved_space)
	{
		this->_is_sliding = false;
		BaseButton::render(pos, reserved_space);

		if (this->_is_held)
		{
			float p_min = pos.x;
			float p_max = pos.x + reserved_space.x;
			float m_pos_x = ImGui::GetMousePos().x;

			float new_value = utils::clamp(
				utils::map(m_pos_x, p_min, p_max, this->_min_value, this->_max_value),
				this->_min_value,
				this->_max_value
			);

			if (new_value != this->_value)
			{
				this->_value = new_value;
				this->_is_sliding = true;
			}
		}

		if (this->_is_sliding) this->on_slide_call();

		return pos;
	}
}