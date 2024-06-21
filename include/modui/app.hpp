#pragma once

#include "core/basewidget.hpp"
#include "ui/widget.hpp"
#include "theme.hpp"

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

		ThemeManager& get_theme_manager();
		Theme& get_current_theme();

		bool is_rendering();

		void pre_render();
		void render();
		void post_render();

	private:
		ui::Widget* _root_widget;
		bool _fullscreen;
		std::string _window_title;
		ThemeManager _theme_manager;
		Theme* _current_theme;
		bool _prerendered;
		bool _rendering;
	};
}