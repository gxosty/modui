#include <modui/app.hpp>
#include <modui/ui/button/button.hpp>
#include "internal/internal_core.hpp"
#include "internal/internal_utils.hpp"

#include <cmath>
#include <stdio.h>

#include <imgui/imgui.h>

namespace modui
{
	App::App() :
		_fullscreen{false},
		_root_widget{nullptr},
		_window_title{"Window " + std::to_string(modui::internal::__get_next_id_for_widget())},
		_prerendered{false},
		_rendering{false},
		_window_open{true}
	{
		this->_theme_manager.add(Theme(std::string(DEFAULT_THEME_LIGHT)));
		this->_theme_manager.add(Theme(std::string(DEFAULT_THEME_DARK)));

		Theme& dark_theme = this->_theme_manager.get(DEFAULT_THEME_DARK);

		dark_theme().primary                   = MODUI_COLOR_HEX(0xFFD0BCFF);
		dark_theme().on_primary                = MODUI_COLOR_HEX(0xFF381E72);
		dark_theme().primary_container         = MODUI_COLOR_HEX(0xFF4F378B);
		dark_theme().on_primary_container      = MODUI_COLOR_HEX(0xFFEADDFF);

		dark_theme().secondary                 = MODUI_COLOR_HEX(0xFFCCC2DC);
		dark_theme().on_secondary              = MODUI_COLOR_HEX(0xFF332D41);
		dark_theme().secondary_container       = MODUI_COLOR_HEX(0xFF4A4458);
		dark_theme().on_secondary_container    = MODUI_COLOR_HEX(0xFFE8DEF8);

		dark_theme().tertiary                  = MODUI_COLOR_HEX(0xFFEFB8C8);
		dark_theme().on_tertiary               = MODUI_COLOR_HEX(0xFF492532);
		dark_theme().tertiary_container        = MODUI_COLOR_HEX(0xFF633B48);
		dark_theme().on_tertiary_container     = MODUI_COLOR_HEX(0xFFFFD8E4);

		dark_theme().error                     = MODUI_COLOR_HEX(0xFFF2B8B5);
		dark_theme().on_error                  = MODUI_COLOR_HEX(0xFF601410);
		dark_theme().error_container           = MODUI_COLOR_HEX(0xFF8C1D18);
		dark_theme().on_error_container        = MODUI_COLOR_HEX(0xFFF9DEDC);

		dark_theme().surface                   = MODUI_COLOR_HEX(0xFF141218);
		dark_theme().on_surface                = MODUI_COLOR_HEX(0xFFE6E0E9);
		dark_theme().surface_variant           = MODUI_COLOR_HEX(0xFF49454F);
		dark_theme().on_surface_variant        = MODUI_COLOR_HEX(0xFFCAC4D0);
		dark_theme().surface_container_highest = MODUI_COLOR_HEX(0xFF36343B);
		dark_theme().surface_container_high    = MODUI_COLOR_HEX(0xFF2B2930);
		dark_theme().surface_container         = MODUI_COLOR_HEX(0xFF211F26);
		dark_theme().surface_container_low     = MODUI_COLOR_HEX(0xFF1D1B20);
		dark_theme().surface_container_lowest  = MODUI_COLOR_HEX(0xFF0F0D13);
		dark_theme().inverse_surface           = MODUI_COLOR_HEX(0xFFE6E0E9);
		dark_theme().inverse_on_surface        = MODUI_COLOR_HEX(0xFF322F35);
		dark_theme().surface_tint              = MODUI_COLOR_HEX(0xFFD0BCFF);

		dark_theme().outline                   = MODUI_COLOR_HEX(0xFF938F99);
		dark_theme().outline_variant           = MODUI_COLOR_HEX(0xFF49454F);

		this->set_current_theme(DEFAULT_THEME_LIGHT);
		this->_queued_callbacks.reserve(10);
	};

	App::App(const std::string& window_title) : App()
	{
		this->set_window_title(window_title);
	}

	App* App::set_window_title(const std::string& window_title)
	{
		this->_window_title = window_title;
		return this;
	}

	App* App::set_window_size(Vec2 window_size)
	{
		this->_window_size = window_size;
		return this;
	}

	App* App::set_window_fullscreen(bool fullscreen)
	{
		this->_fullscreen = fullscreen;
		return this;
	}

	App* App::set_window_open(bool open)
	{
		this->_window_open = open;

		return this;
	}

	void App::pre_render()
	{
		if (this->_prerendered) return;

		modui::internal::__set_current_app(this);
		this->_root_widget = this->build()->build_widget();
		this->_root_widget->pre_render();
		this->_window_close_button = ui::Button::init()
			->set_size(Vec2(utils::dp(20), utils::dp(20)))
			->on_release(MODUI_CALLBACK(this) {
				this->_window_open = false;
			});
		this->_window_close_button->pre_render();
		modui::internal::__set_current_app(nullptr);

		bool opened = false;

		if (!this->_fullscreen)
			ImGui::SetNextWindowSize(this->_window_size);
		
		ImGui::Begin(this->_window_title.c_str(), &opened);
		this->_window = ImGui::GetCurrentWindow();
		ImGui::End();

		this->_prerendered = true;
	}

	void App::render()
	{
		if (!this->_window_open) return;

		int window_flags =
			  ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar
			| ImGuiWindowFlags_NoScrollWithMouse
			| ImGuiWindowFlags_NoTitleBar;

		int pop_style_var_count = 9;
		int pop_style_col_count = 5;

		if (this->_fullscreen)
		{
			window_flags =
				  ImGuiWindowFlags_NoTitleBar
				| ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoMove;

			ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
			ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
		}

		Theme& theme = this->get_current_theme();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, theme().surface);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, theme().surface);
		ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);
		ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, 0);
		ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, theme().secondary);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, this->_fullscreen ? 0.0f : utils::dp(15));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0.0f, 0.0f));

		if (!ImGui::Begin(this->_window_title.c_str(), &this->_window_open, window_flags))
		{
			ImGui::End();

			ImGui::PopStyleVar(pop_style_var_count);
			ImGui::PopStyleColor(pop_style_col_count);
			return;
		}


		if (!ImGui::IsWindowCollapsed())
		{

			this->_rendering = true;
			modui::internal::__set_current_app(this);

			if (!this->_fullscreen) _render_window_title();
			Vec2 cursor_pos = ImGui::GetCursorScreenPos();
			Vec2 avail_size = ImGui::GetContentRegionAvail();

			this->_root_widget->calculate_size(avail_size);
			this->_root_widget->render(cursor_pos, avail_size);
			this->_drain_queued_callbacks();

			modui::internal::__set_current_app(nullptr);
			this->_rendering = false;
		}

		ImGui::End();

		ImGui::PopStyleVar(pop_style_var_count);
		ImGui::PopStyleColor(pop_style_col_count);
	}

	void App::post_render()
	{
		this->_prerendered = false;
		delete this->_root_widget;
		this->_root_widget = nullptr;
	}

	void App::add_callback_to_queue(ui::Widget* widget, ButtonInputCallback* callback)
	{
		this->_queued_callbacks.emplace_back(widget, callback);
	}

	ThemeManager& App::get_theme_manager()
	{
		return this->_theme_manager;
	}

	Theme& App::get_current_theme()
	{
		return *this->_current_theme;
	}

	void App::set_current_theme(const std::string& theme_name)
	{
		this->_current_theme = &this->_theme_manager.get(theme_name);
	}

	ImDrawListSplitter& App::get_draw_list_splitter()
	{
		return this->_draw_list_splitter;
	}

	bool App::is_window_open()
	{
		return this->_window_open;
	}

	bool App::is_rendering()
	{
		return this->_rendering;
	}

	void App::_render_window_title()
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		Vec2 cursor_pos = ImGui::GetCursorScreenPos();
		Vec2 title_pos = Vec2(cursor_pos.x + utils::dp(15), cursor_pos.y + utils::dp(5));
		draw_list->AddText(ImGui::GetFont(), utils::dp(20), title_pos, this->get_current_theme()().on_surface, this->_window_title.c_str(), nullptr);

		Vec2 close_button_pos = Vec2(cursor_pos.x + ImGui::GetContentRegionAvail().x - utils::dp(25), cursor_pos.y + utils::dp(5));
		this->_window_close_button->calculate_size(Vec2(utils::dp(20), utils::dp(20)));
		this->_window_close_button->render(close_button_pos, Vec2(utils::dp(20), utils::dp(20)));

		ImGui::SetCursorScreenPos(Vec2(cursor_pos.x, cursor_pos.y + utils::dp(25)));
	}

	void App::_drain_queued_callbacks()
	{
		for (auto& i : this->_queued_callbacks)
		{
			(*(i.second))(i.first);
		}

		this->_queued_callbacks.clear();
	}
}