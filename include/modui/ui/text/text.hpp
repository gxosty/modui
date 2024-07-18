#pragma once

#include "../../core/common.hpp"
#include "../widget.hpp"

#include <string>

namespace modui::ui
{
	class Text : public Widget
	{
	public:
		Text(const std::string& text);
		static Text* init(const std::string& text = "");

		Text* set_side(modui::Side side) override;

		Text* set_text(const std::string& text) override;
		Text* set_font_size(float font_size) override;

		void pre_render() override;
		Vec2 render(Vec2 pos, Vec2 reserved_space) override;

		float calculate_size_x(float reserved_space_x) override;
		float calculate_size_y(float reserved_space_y) override;

	private:
		std::string _text;
		float _font_size;
		Vec2 _text_size_v;
		modui::Side _side;

		void _update_text_size_v(float available_width = 0.0f);

		Vec2 _calc_side();

		virtual bool is_on_card();
	};

	class TitleText : public Text
	{
	public:
		TitleText(const std::string& text);
		static TitleText* init(const std::string& text = "");

	private:
		bool is_on_card() override;
	};
}