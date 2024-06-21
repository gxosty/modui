#include <modui/app.hpp>
#include "internal/internal_core.hpp"
#include "internal/internal_utils.hpp"

#include <cmath>
#include <stdio.h>

#include <imgui/imgui.h>

namespace modui
{
	App::App() :
		_fullscreen{true},
		_root_widget{nullptr},
		_window_title{"Window " + std::to_string(modui::internal::__get_next_id_for_widget())},
		_prerendered{false},
		_rendering{false}
	{
		this->_theme_manager.add(Theme(std::string(DEFAULT_THEME_NAME)));
		this->_current_theme = &this->_theme_manager.get(std::string(DEFAULT_THEME_NAME));
	};

	App::App(const std::string& window_title) : App()
	{
		this->set_window_title(window_title);
	}

	// void App::run()
	// {
	// 	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// 	this->_fullscreen = true;

	// 	bool done = false;

	// 	while (!done)
	// 	{
	// 		SDL_Event event;
	// 		while (SDL_PollEvent(&event))
	// 		{
	// 			ImGui_ImplSDL2_ProcessEvent(&event);
	// 			if (event.type == SDL_QUIT)
	// 				done = true;
	// 			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
	// 				done = true;
	// 		}

	// 		// Start the Dear ImGui frame
	// 		ImGui_ImplOpenGL3_NewFrame();
	// 		ImGui_ImplSDL2_NewFrame();
	// 		ImGui::NewFrame();

	// 		if (!this->_prerendered)
	// 		{
	// 			this->_pre_render();
	// 		}

	// 		this->_render();

	// 		// Rendering
	// 		ImGui::Render();
	// 		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	// 		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	// 		glClear(GL_COLOR_BUFFER_BIT);
	// 		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// 		SDL_GL_SwapWindow(window);
	// 	}

	// 	this->_fullscreen = false;
	// 	this->_post_render();

	// 	return;
	// }

	App* App::set_window_title(const std::string& window_title)
	{
		this->_window_title = window_title;
		return this;
	}

	void App::pre_render()
	{
		if (this->_prerendered) return;

		modui::internal::__set_current_app(this);
		this->_root_widget = this->build()->build_widget();
		this->_root_widget->pre_render();
		modui::internal::__set_current_app(nullptr);
		this->_prerendered = true;
	}

	void App::render()
	{
		int window_flags = 0;

		if (this->_fullscreen)
		{
			window_flags = \
				  ImGuiWindowFlags_NoTitleBar
				| ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoMove
				| ImGuiWindowFlags_NoCollapse
				| ImGuiWindowFlags_NoScrollbar
				| ImGuiWindowFlags_NoScrollWithMouse;

			ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
			ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
		}

		Theme& theme = this->get_current_theme();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, theme().surface);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, theme().surface);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0.0f, 0.0f));

		if (!ImGui::Begin(this->_window_title.c_str(), NULL, window_flags))
		{
			ImGui::End();
			return;
		}


		if (!ImGui::IsWindowCollapsed())
		{
			modui::internal::__set_current_app(this);
			this->_rendering = true;
			Vec2 cursor_pos = ImGui::GetCursorScreenPos();
			Vec2 avail_size = ImGui::GetContentRegionAvail();

			this->_root_widget->render(cursor_pos, avail_size);
			modui::internal::__set_current_app(nullptr);
			this->_rendering = false;
		}

		ImGui::End();

		ImGui::PopStyleVar(9);
		ImGui::PopStyleColor(2);
	}

	void App::post_render()
	{
		this->_prerendered = false;
		delete this->_root_widget;
		this->_root_widget = nullptr;
	}

	ThemeManager& App::get_theme_manager()
	{
		return this->_theme_manager;
	}

	Theme& App::get_current_theme()
	{
		return *this->_current_theme;
	}

	bool App::is_rendering()
	{
		return this->_rendering;
	}
}