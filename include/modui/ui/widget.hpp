#pragma once

#include "../core/basewidget.hpp"
#include "../core/common.hpp"
#include "../theme.hpp"

#include <string>
#include <vector>

namespace modui::ui
{
	class Widget : core::BaseWidget
	{
	public:
		friend class modui::App;

		Widget();
		virtual ~Widget();
		static Widget* init();

		virtual Widget* add(Widget* widget);
		virtual Widget* remove(Widget* widget);

		virtual void pre_render();
		virtual Vec2 render(Vec2 pos, Vec2 reserved_space);
		virtual void post_render();

		Widget* set_id(const std::string& id);
		const std::string& get_id();
		Widget* find_widget_by_id(const std::string& id);

		Widget* get_parent(); // ONLY ui::Widget*
		Vec2 get_pos();

		Widget* set_size(const Vec2& size);
		Widget* set_size_x(float x);
		Widget* set_size_y(float y);
		Vec2 get_size();
		Vec2 get_calculated_size();

		Theme& get_theme();

		Widget* build_widget();

		Widget* operator()(Widget* widget)
		{
			this->add(widget);
			return this;
		}

		template<typename... Args>
		Widget* add(Widget* widget, Args... args)
		{
			this->add(widget);
			return this->add(args...);
		}

		// placeholder for inherited objects, DON'T TOUCH
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_orientation(modui::LayoutOrientation orientation);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_side(modui::Side side);

		MODUI_VIRTUAL_PLACEHOLDER   Widget* on_press(ButtonInputCallback callback);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* on_hold(ButtonInputCallback callback);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* on_release(ButtonInputCallback callback);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* on_slide(ButtonInputCallback callback);

		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_text(const std::string& text);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_supporting_text(const std::string& supporting_text);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_trailing_text(const std::string& trailing_text);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_font_size(float font_size);

		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_icon(ImageID icon);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_leading_icon(ImageID leading_icon);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_icon_size(float icon_size);

		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_trailing_widget(Widget* trailing_widget);

		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_value(float value);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_state(bool state);
		MODUI_VIRTUAL_PLACEHOLDER   bool    get_state();
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_toggleable(bool toggleable);

		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_padding(Vec2 padding);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_padding(Vec4 padding);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_padding(float x, float y);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_padding(float top, float right, float bottom, float left);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_padding(float padding);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_padding_top(float padding);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_padding_right(float padding);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_padding_bottom(float padding);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_padding_left(float padding);
		                            Vec4    get_padding();

		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_spacing(Vec2 spacing);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_spacing(float x, float y);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_spacing(float spacing);
		                            Vec2    get_spacing();

		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_name(const std::string& name);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_screen(const std::string& screen_name);

		// For custom widgets and internal use!
		virtual float calculate_size_x(float reserved_space_x);
		virtual float calculate_size_y(float reserved_space_y);

	protected:
		int _id;
		std::string _name_id;
		core::BaseWidget* _parent;

		Vec2 _pos;
		Vec2 _size;
		Vec2 _calculated_size;
		Vec4 _padding;
		Vec2 _spacing;

		Theme** _theme;
		std::vector<Widget*> _children;

		Vec2 calculate_size(Vec2 reserved_space);

		static void push_on_card();
		static void pop_on_card();
		static bool is_on_card();

	private:
		static int _on_card;
		Widget* _root_widget;
		bool _built;

		void _set_parent(core::BaseWidget* bwidget);
		virtual void on_create_widget();
		void _set_root_widget(Widget*);
	};
}