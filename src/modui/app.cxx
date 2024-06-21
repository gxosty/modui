#include <modui/app.hpp>
#include "internal/internal_core.hpp"
#include "internal/internal_utils.hpp"

#include <cmath>
#include <stdio.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>

#ifdef MODUI_BACKEND_SDL2
	#include <imgui/imgui_impl_sdl2.h>

	#include <SDL2/SDL.h>

	#if defined(IMGUI_IMPL_OPENGL_ES2)
		#include <SDL2/SDL_opengles2.h>
	#else
		#include <SDL2/SDL_opengl.h>
	#endif

	#ifdef __EMSCRIPTEN__
		#include "../libs/emscripten/emscripten_mainloop_stub.h"
	#endif
#endif // MODUI_BACKEND_SDL2

static void glfw_error_callback(int error, const char* description)
{
	printf("GLFW Error %d: %s\n", error, description);
	// fprintf(stderr, "GLFW Error %d: %s\n", error, description);
	return;
}

namespace modui
{
	App::App() :
		_imgui_window{true},
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

#ifdef MODUI_BACKEND_SDL2
	void App::run()
	{
		// Setup SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
		{
			printf("Error: %s\n", SDL_GetError());
			return;
		}

		// Decide GL+GLSL versions
	#if defined(IMGUI_IMPL_OPENGL_ES2)
		// GL ES 2.0 + GLSL 100
		const char* glsl_version = "#version 100";
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	#elif defined(__APPLE__)
		// GL 3.2 Core + GLSL 150
		const char* glsl_version = "#version 150";
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	#else
		// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	#endif

	#ifdef SDL_HINT_IME_SHOW_UI
		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
	#endif

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		SDL_Window* window = SDL_CreateWindow(this->_window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, window_flags);
		if (window == nullptr)
		{
			printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
			return;
		}

		SDL_GLContext gl_context = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, gl_context);
		SDL_GL_SetSwapInterval(1); // Enable vsync

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
		ImGui_ImplOpenGL3_Init(glsl_version);

		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		this->_imgui_window = false;

		bool done = false;

	#ifdef __EMSCRIPTEN__
		io.IniFilename = nullptr;
		EMSCRIPTEN_MAINLOOP_BEGIN
	#else
		while (!done)
	#endif
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				ImGui_ImplSDL2_ProcessEvent(&event);
				if (event.type == SDL_QUIT)
					done = true;
				if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
					done = true;
			}

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();

			if (!this->_prerendered)
			{
				this->_pre_render();
			}

			this->_render();

			// Rendering
			ImGui::Render();
			glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
			glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			SDL_GL_SwapWindow(window);
		}
	#ifdef __EMSCRIPTEN__
		EMSCRIPTEN_MAINLOOP_END;
	#endif

		this->_imgui_window = true;
		this->_post_render();

		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		SDL_GL_DeleteContext(gl_context);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return;
	}
#endif // MODUI_BACKEND_SDL2

	App* App::set_window_title(const std::string& window_title)
	{
		this->_window_title = window_title;
		return this;
	}

	void App::_pre_render()
	{
		modui::internal::__set_current_app(this);
		this->_root_widget = this->build()->build_widget();
		this->_root_widget->pre_render();
		modui::internal::__set_current_app(nullptr);
		this->_prerendered = true;
	}

	void App::_render()
	{
		int window_flags = 0;

		if (!this->_imgui_window)
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

	void App::_post_render()
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