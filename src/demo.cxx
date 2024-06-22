#include <modui/app.hpp>
#include <modui/ui/widgets.hpp>

#include <iostream>
#include <cmath>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_win32.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <GL/GL.h>
#include <tchar.h>

namespace ui = modui::ui;





class MyApp : public modui::App
{
public:
	MyApp() : modui::App("MyApp")
	{
		this->set_window_fullscreen(false);
		this->set_window_size(Vec2(600, 300));
	}

	virtual ui::Widget* build() override
	{
		this->screen_manager = ui::ScreenManager::init();

		return
		this->screen_manager->add(
			ui::Screen::init("demo_screen1")
				->add(
					ui::ScrollLayout::init()
						->add(
							ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_VERTICAL)
								->set_padding(DP(5))
								->set_spacing(DP(5))
								->add(
									ui::Text::init("ModUI Demo"),
									
									ui::Button::init("Button"),
									
									ui::Button::init("width dp(150) button")
										->set_size_x(DP(150)),
									
									ui::Button::init("Full width button")
										->set_size_x(MODUI_SIZE_WIDTH_FULL),

									ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_HORIZONTAL)
										->set_spacing(DP(5))
										->set_size_y(0.0f)
										->add(
											ui::Text::init("Checkboxes")
												->set_size_y(DP(20)),

											ui::Checkbox::init(),
											ui::Checkbox::init()
										),

									ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_HORIZONTAL)
										->set_spacing(DP(5))
										->set_size_y(0.0f)
										->add(
											ui::Text::init("Slider")
												->set_size_y(DP(20)),

											ui::Slider::init(0.0f, 100.0f)
												->on_slide(MODUI_CALLBACK(this) {
													ui::Text* text = (ui::Text*)this->screen_manager->find_widget_by_id("slider_value");
													ui::Slider* slider = (ui::Slider*)this_widget;

													text->set_text("Slider value: " + std::to_string(slider->get_value()));
												})
										),

									ui::Text::init("Slider value: 0.0")
										->set_id("slider_value"),

									ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_HORIZONTAL)
										->set_spacing(DP(5))
										->add(
											ui::FilledCard::init()
												// ->set_size_x(DP(150))
												->set_size_y(0.0f) // 0.0f means adaptive height
												->set_padding(DP(10))
												->set_spacing(DP(5))
												->add(
													ui::Text::init("Card Title 1")
														->set_font_size(DP(18)),

													ui::Text::init("Example card content, just for demo (or call it a placeholder)"),

													ui::Button::init("Open")
												),

											ui::FilledCard::init()
												// ->set_size_x(DP(150))
												->set_size_y(0.0f)
												->set_padding(DP(10))
												->set_spacing(DP(5))
												->add(
													ui::Text::init("Card Title 2")
														->set_font_size(DP(18)),

													ui::Text::init("Example card content, just for demo (or call it a placeholder)"),

													ui::Button::init("Open")
												)
										),

									ui::Button::init("Toggle theme")
										->on_release(MODUI_CALLBACK(this) {
											if (!this->dark_theme)
											{
												this->set_current_theme(DEFAULT_THEME_DARK);
												this->dark_theme = true;
											}
											else
											{
												this->set_current_theme(DEFAULT_THEME_LIGHT);
												this->dark_theme = false;
											}
										})

								)
						)
				)
		);
	}

private:
	ui::ScreenManager* screen_manager;
	bool dark_theme = false;
};





// Data stored per platform window
struct WGL_WindowData { HDC hDC; };

// Data
static HGLRC            g_hRC;
static WGL_WindowData   g_MainWindow;
static int              g_Width;
static int              g_Height;

// Forward declarations of helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data);
void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data);
void ResetDeviceWGL();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main()
{
	// Create application window
	//ImGui_ImplWin32_EnableDpiAwareness();
	WNDCLASSEXW wc = { sizeof(wc), CS_OWNDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
	::RegisterClassExW(&wc);
	HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui Win32+OpenGL3 Example", WS_OVERLAPPEDWINDOW, 100, 100, 470, 600, nullptr, nullptr, wc.hInstance, nullptr);

	// Initialize OpenGL
	if (!CreateDeviceWGL(hwnd, &g_MainWindow))
	{
		CleanupDeviceWGL(hwnd, &g_MainWindow);
		::DestroyWindow(hwnd);
		::UnregisterClassW(wc.lpszClassName, wc.hInstance);
		return 1;
	}
	wglMakeCurrent(g_MainWindow.hDC, g_hRC);

	// Show the window
	::ShowWindow(hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(hwnd);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_InitForOpenGL(hwnd);
	ImGui_ImplOpenGL3_Init();

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 48.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != nullptr);

	// Our state
	ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
	modui::set_screen_density(1.666667f);
	MyApp* app = new MyApp();

	// Main loop
	bool done = false;
	while (!done)
	{
		// Poll and handle messages (inputs, window resize, etc.)
		// See the WndProc() function below for our to dispatch events to the Win32 backend.
		MSG msg;
		while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				done = true;
		}
		if (done)
			break;

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		app->pre_render();
		app->render();

		// Rendering
		ImGui::Render();
		glViewport(0, 0, g_Width, g_Height);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Present
		::SwapBuffers(g_MainWindow.hDC);
	}

	app->post_render();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceWGL(hwnd, &g_MainWindow);
	wglDeleteContext(g_hRC);
	::DestroyWindow(hwnd);
	::UnregisterClassW(wc.lpszClassName, wc.hInstance);

	return 0;
}

// Helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
	HDC hDc = ::GetDC(hWnd);
	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;

	const int pf = ::ChoosePixelFormat(hDc, &pfd);
	if (pf == 0)
		return false;
	if (::SetPixelFormat(hDc, pf, &pfd) == FALSE)
		return false;
	::ReleaseDC(hWnd, hDc);

	data->hDC = ::GetDC(hWnd);
	if (!g_hRC)
		g_hRC = wglCreateContext(data->hDC);
	return true;
}

void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
	wglMakeCurrent(nullptr, nullptr);
	::ReleaseDC(hWnd, data->hDC);
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
		{
			g_Width = LOWORD(lParam);
			g_Height = HIWORD(lParam);
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
