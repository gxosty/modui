#pragma once

#include "../../core/common.hpp"
#include "basebutton.hpp"

#include <string>

namespace modui::ui
{
	class Button : public BaseButton
	{
	public:
		Button(const std::string& text);
		static Button* init(const std::string& text = "");

		Button* set_text(const std::string& text) override;
		const std::string& get_text();

		Button* set_font_size(float font_size) override;

		virtual void pre_render() override;
		virtual Vec2 render(Vec2 pos, Vec2 reserved_space) override;

	private:
		std::string _text;
		float _font_size;
		Vec2 _text_size_v;
		float _rounding;

		void _update_text_size_v();

		float _press_factor;
	};
}