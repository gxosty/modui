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

		virtual Widget* add_widget(Widget* widget);
		virtual Widget* remove_widget(Widget* widget);

		virtual void pre_render();
		virtual Vec2 render(Vec2 pos, Vec2 reserved_space);
		virtual void post_render();

		Widget* set_id(const std::string& id);
		const std::string& get_id();
		Widget* find_widget_by_id(const std::string& id);

		Vec2 get_pos();

		Widget* set_size(const Vec2& size);
		Widget* set_size_x(float x);
		Widget* set_size_y(float y);
		Vec2 get_size();

		Theme& get_theme();

		Widget* build_widget();

		// placeholder for inherited objects, DON'T TOUCH
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_orientation(modui::LayoutOrientation orientation);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_side(modui::Side side);

		MODUI_VIRTUAL_PLACEHOLDER   Widget* on_press(ButtonInputCallback callback);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* on_hold(ButtonInputCallback callback);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* on_release(ButtonInputCallback callback);

		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_text(const std::string& text);
		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_font_size(float font_size);

		MODUI_VIRTUAL_PLACEHOLDER   Widget* set_value(float value);

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

	protected:
		int _id;
		std::string _name_id;
		core::BaseWidget* _parent;

		Vec2 _pos;
		Vec2 _size;
		Vec4 _padding;
		Vec2 _spacing;

		Theme** _theme;
		std::vector<Widget*> _children;

	private:
		Widget* _root_widget;

		void _set_parent(core::BaseWidget* bwidget);
		virtual void on_create_widget();
		void _set_root_widget(Widget*);
	};
}