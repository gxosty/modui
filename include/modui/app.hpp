#pragma once

#include "core/basewidget.hpp"
#include "ui/widget.hpp"
#include "theme.hpp"
#include <imgui/imgui.h>

#include <string>
#include <vector>

namespace modui
{
	class App : core::BaseWidget
	{
		friend class ui::Widget;

	public:
		App();
		App(const std::string& window_title);

		// void run();
		virtual ui::Widget* build() = 0;

		App* set_window_title(const std::string& window_title);
		App* set_window_size(Vec2 window_size);
		App* set_window_fullscreen(bool fullscreen);
		App* set_window_open(bool open);

		ThemeManager& get_theme_manager();
		Theme& get_current_theme();
		ImDrawListSplitter& get_draw_list_splitter();

		void set_current_theme(const std::string& theme_name);

		bool is_window_open();
		bool is_rendering();

		void pre_render();
		void render();
		void post_render();

		void add_callback_to_queue(ui::Widget* widget, ButtonInputCallback* callback);

	private:
		ImGuiWindow* _window;
		ui::Widget* _root_widget;
		bool _fullscreen;
		std::string _window_title;
		Vec2 _window_size; // only when not fullscreen
		bool _window_open;
		ThemeManager _theme_manager;
		Theme* _current_theme;
		bool _prerendered;
		bool _rendering;

		std::vector<
			std::pair<ui::Widget*, ButtonInputCallback*>
		> _queued_callbacks;

		ImDrawListSplitter _draw_list_splitter;

		ui::Widget* _window_close_button;
		void _render_window_title();
		void _drain_queued_callbacks();
	};
}