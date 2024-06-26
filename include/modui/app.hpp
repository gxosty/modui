#pragma once

#include "core/basewidget.hpp"
#include "ui/widget.hpp"
#include "theme.hpp"
#include <imgui/imgui.h>

#include <string>

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

		ThemeManager& get_theme_manager();
		Theme& get_current_theme();
		ImDrawListSplitter& get_draw_list_splitter();

		void set_current_theme(const std::string& theme_name);

		bool is_rendering();

		void pre_render();
		void render();
		void post_render();

	private:
		ImGuiWindow* _window;
		ui::Widget* _root_widget;
		bool _fullscreen;
		std::string _window_title;
		Vec2 _window_size; // only when not fullscreen
		ThemeManager _theme_manager;
		Theme* _current_theme;
		bool _prerendered;
		bool _rendering;

		ImDrawListSplitter _draw_list_splitter;
	};
}