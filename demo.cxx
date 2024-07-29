#include <modui/modui.hpp>

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
		this->set_window_size(Vec2(480, 480));
		// this->set_window_fullscreen(true);

		modui::Theme theme_light("theme_light");

		theme_light().primary                   = MODUI_COLOR_HEX(0xFF'233AD1);
		theme_light().on_primary                = MODUI_COLOR_HEX(0xFF'FFFFFF);
		theme_light().primary_container         = MODUI_COLOR_HEX(0xFF'4F65F7);
		theme_light().on_primary_container      = MODUI_COLOR_HEX(0xFF'FFFFFF);

		theme_light().secondary                 = MODUI_COLOR_HEX(0xFF'515A98);
		theme_light().on_secondary              = MODUI_COLOR_HEX(0xFF'FFFFFF);
		theme_light().secondary_container       = MODUI_COLOR_HEX(0xFF'BCC3FF);
		theme_light().on_secondary_container    = MODUI_COLOR_HEX(0xFF'28316C);

		theme_light().tertiary                  = MODUI_COLOR_HEX(0xFF'891595);
		theme_light().on_tertiary               = MODUI_COLOR_HEX(0xFF'FFFFFF);
		theme_light().tertiary_container        = MODUI_COLOR_HEX(0xFF'B445BE);
		theme_light().on_tertiary_container     = MODUI_COLOR_HEX(0xFF'FFFFFF);

		theme_light().error                     = MODUI_COLOR_HEX(0xFF'BA1A1A);
		theme_light().on_error                  = MODUI_COLOR_HEX(0xFF'FFFFFF);
		theme_light().error_container           = MODUI_COLOR_HEX(0xFF'FFDAD6);
		theme_light().on_error_container        = MODUI_COLOR_HEX(0xFF'410002);

		theme_light().surface                   = MODUI_COLOR_HEX(0xFF'FBF8FF);
		theme_light().on_surface                = MODUI_COLOR_HEX(0xFF'1A1B24);
		theme_light().surface_variant           = MODUI_COLOR_HEX(0xFF'E1E1F4);
		theme_light().on_surface_variant        = MODUI_COLOR_HEX(0xFF'444655);
		theme_light().surface_container_highest = MODUI_COLOR_HEX(0xFF'E3E1ED);
		theme_light().surface_container_high    = MODUI_COLOR_HEX(0xFF'E8E7F3);
		theme_light().surface_container         = MODUI_COLOR_HEX(0xFF'EEECF9);
		theme_light().surface_container_low     = MODUI_COLOR_HEX(0xFF'F4F2FF);
		theme_light().surface_container_lowest  = MODUI_COLOR_HEX(0xFF'FFFFFF);
		theme_light().inverse_surface           = MODUI_COLOR_HEX(0xFF'2F3039);
		theme_light().inverse_on_surface        = MODUI_COLOR_HEX(0xFF'F1EFFC);
		theme_light().surface_tint              = MODUI_COLOR_HEX(0xFF'364CDF);

		theme_light().outline                   = MODUI_COLOR_HEX(0xFF'757687);
		theme_light().outline_variant           = MODUI_COLOR_HEX(0xFF'C5C5D8);

		this->get_theme_manager().add(theme_light);

		modui::Theme theme_dark("theme_dark");

		theme_dark().primary                   = MODUI_COLOR_HEX(0xFF'BCC3FF);
		theme_dark().on_primary                = MODUI_COLOR_HEX(0xFF'001A98);
		theme_dark().primary_container         = MODUI_COLOR_HEX(0xFF'4F64F6);
		theme_dark().on_primary_container      = MODUI_COLOR_HEX(0xFF'FFFFFF);

		theme_dark().secondary                 = MODUI_COLOR_HEX(0xFF'BCC3FF);
		theme_dark().on_secondary              = MODUI_COLOR_HEX(0xFF'222B66);
		theme_dark().secondary_container       = MODUI_COLOR_HEX(0xFF'323A76);
		theme_dark().on_secondary_container    = MODUI_COLOR_HEX(0xFF'CED2FF);

		theme_dark().tertiary                  = MODUI_COLOR_HEX(0xFF'FFA9FF);
		theme_dark().on_tertiary               = MODUI_COLOR_HEX(0xFF'590062);
		theme_dark().tertiary_container        = MODUI_COLOR_HEX(0xFF'B344BD);
		theme_dark().on_tertiary_container     = MODUI_COLOR_HEX(0xFF'FFFFFF);

		theme_dark().error                     = MODUI_COLOR_HEX(0xFF'FFB4AB);
		theme_dark().on_error                  = MODUI_COLOR_HEX(0xFF'690005);
		theme_dark().error_container           = MODUI_COLOR_HEX(0xFF'93000A);
		theme_dark().on_error_container        = MODUI_COLOR_HEX(0xFF'FFDAD6);

		theme_dark().surface                   = MODUI_COLOR_HEX(0xFF'12131B);
		theme_dark().on_surface                = MODUI_COLOR_HEX(0xFF'E3E1ED);
		theme_dark().surface_variant           = MODUI_COLOR_HEX(0xFF'444655);
		theme_dark().on_surface_variant        = MODUI_COLOR_HEX(0xFF'C5C5D8);
		theme_dark().surface_container_highest = MODUI_COLOR_HEX(0xFF'33343D);
		theme_dark().surface_container_high    = MODUI_COLOR_HEX(0xFF'292932);
		theme_dark().surface_container         = MODUI_COLOR_HEX(0xFF'1E1F28);
		theme_dark().surface_container_low     = MODUI_COLOR_HEX(0xFF'1A1B24);
		theme_dark().surface_container_lowest  = MODUI_COLOR_HEX(0xFF'0D0E16);
		theme_dark().inverse_surface           = MODUI_COLOR_HEX(0xFF'E3E1ED);
		theme_dark().inverse_on_surface        = MODUI_COLOR_HEX(0xFF'2F3039);
		theme_dark().surface_tint              = MODUI_COLOR_HEX(0xFF'BCC3FF);

		theme_dark().outline                   = MODUI_COLOR_HEX(0xFF'8F8FA1);
		theme_dark().outline_variant           = MODUI_COLOR_HEX(0xFF'444655);

		this->get_theme_manager().add(theme_dark);
		this->set_current_theme("theme_light");
	}

	virtual ui::Widget* build() override
	{
		this->screen_manager = ui::ScreenManager::init();

		// this->set_current_theme(DEFAULT_THEME_DARK);

		ImageID selectable_favorite = modui::image::Image::make_selectable(
			modui::icons::ic_favorite_outline,
			modui::icons::ic_favorite
		);

		return
		this->screen_manager->add(
			ui::Screen::init("demo_screen1")
				->add(
					ui::ScrollLayout::init()
						->add(
							ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_VERTICAL)
								->set_padding(DP(10.0f))
								->set_spacing(DP(10.0f))
								->set_size_x(MODUI_SIZE_WIDTH_FULL)
								->set_size_y(MODUI_SIZE_HEIGHT_WRAP)
								->add(
									ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_HORIZONTAL)
										->set_size_y(MODUI_SIZE_HEIGHT_WRAP)
										->set_spacing(DP(5))
										->add(
											ui::ListItem::init("Dark Theme", "", "", modui::icons::ic_dark_mode, ui::Switch::init())
												->on_release(MODUI_CALLBACK(this) {
													if (this->dark_theme)
													{
														this->set_current_theme("theme_light");
													}
													else
													{
														this->set_current_theme("theme_dark");
													}

													this->dark_theme = !this->dark_theme;
												})
										),

									ui::Button::init("Button"),

									ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_HORIZONTAL)
										->set_size_y(MODUI_SIZE_HEIGHT_WRAP)
										->set_spacing(DP(10))
										->add(
											ui::Text::init("Checkbox: ")
												->set_size_y(MODUI_SIZE_HEIGHT_FULL),

											ui::Checkbox::init(),
											ui::Checkbox::init(true),
											ui::Widget::init()
												->set_size_x(MODUI_SIZE_WIDTH_FULL),

											ui::Text::init("Switch: ")
												->set_size_y(MODUI_SIZE_HEIGHT_FULL),
											
											ui::Switch::init(),
											ui::Switch::init(true),
											ui::Widget::init()
												->set_size_x(MODUI_SIZE_WIDTH_FULL)
										),

									ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_HORIZONTAL)
										->set_size_y(MODUI_SIZE_HEIGHT_WRAP)
										->set_spacing(DP(10))
										->add(
											ui::Text::init("Slider: ")
												->set_size_y(MODUI_SIZE_HEIGHT_FULL),
											
											ui::Slider::init(0.0f, 100.0f)
										),

									ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_HORIZONTAL)
										->set_size_y(MODUI_SIZE_HEIGHT_WRAP)
										->set_spacing(DP(10))
										->add(
											ui::Text::init("FilledIconButton: ")
												->set_size_y(MODUI_SIZE_HEIGHT_FULL),

											ui::FilledIconButton::init(selectable_favorite)
												->set_state(false),
											ui::FilledIconButton::init(selectable_favorite)
												->set_state(true),
											ui::FilledIconButton::init(selectable_favorite)
												->set_state(false)
												->set_toggleable(true)
										),

									ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_HORIZONTAL)
										->set_size_y(MODUI_SIZE_HEIGHT_WRAP)
										->set_spacing(DP(10))
										->add(
											ui::Text::init("FilledTonalIconButton: ")
												->set_size_y(MODUI_SIZE_HEIGHT_FULL),

											ui::FilledTonalIconButton::init(selectable_favorite)
												->set_state(false),
											ui::FilledTonalIconButton::init(selectable_favorite)
												->set_state(true),
											ui::FilledTonalIconButton::init(selectable_favorite)
												->set_state(false)
												->set_toggleable(true)
										),

									ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_HORIZONTAL)
										->set_size_y(MODUI_SIZE_HEIGHT_WRAP)
										->set_spacing(DP(10))
										->add(
											ui::Text::init("OutlinedIconButton: ")
												->set_size_y(MODUI_SIZE_HEIGHT_FULL),

											ui::OutlinedIconButton::init(selectable_favorite)
												->set_state(false),
											ui::OutlinedIconButton::init(selectable_favorite)
												->set_state(true),
											ui::OutlinedIconButton::init(selectable_favorite)
												->set_state(false)
												->set_toggleable(true)
										),

									ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_HORIZONTAL)
										->set_size_y(MODUI_SIZE_HEIGHT_WRAP)
										->set_spacing(DP(10))
										->add(
											ui::Text::init("IconButton: ")
												->set_size_y(MODUI_SIZE_HEIGHT_FULL),

											ui::IconButton::init(selectable_favorite)
												->set_state(false),
											ui::IconButton::init(selectable_favorite)
												->set_state(true),
											ui::IconButton::init(selectable_favorite)
												->set_state(false)
												->set_toggleable(true)
										),

									ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_VERTICAL)
										->set_size_y(MODUI_SIZE_HEIGHT_WRAP)
										->add(
											ui::ListItem::init("One Line ListItem"),
											ui::ListItem::init("Two Line ListItem", "Example supporting text"),
											ui::ListItem::init("Three Line ListItem", "Example supporting text that is long enough to fill the third line", "+999", nullptr, nullptr, ui::ListItem::Type::THREE_LINED),
											ui::ListItem::init("ListItem with trailing text", "Example supporting text", "+999"),
											ui::ListItem::init("ListItem with control widget", "Example supporting text", "", nullptr,
												ui::Checkbox::init(true)
											),
											ui::ListItem::init("ListItem with leading icon", "Example supporting text", "", modui::icons::ic_settings_outline),
											ui::ListItem::init("ListItem Full", "Example supporting text that is long enough to fill the third line", "", modui::icons::ic_favorite_outline,
												ui::Switch::init(true),
												ui::ListItem::Type::THREE_LINED
											)
										),

									ui::FilledCard::init(modui::LAYOUT_ORIENTATION_VERTICAL)
										->set_size_x(MODUI_SIZE_WIDTH_FULL)
										->set_padding(DP(15))
										->set_spacing(DP(15))
										->add(
											ui::TitleText::init("Card Title"),

											ui::Text::init("Reference site about Lorem Ipsum, giving information on its origins, as well as a random Lipsum generator.")
										)
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
	HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui Win32+OpenGL3 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 720, nullptr, nullptr, wc.hInstance, nullptr);

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
	// io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
	io.Fonts->AddFontFromFileTTF("../DroidSans.ttf", 14.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != nullptr);

	// Our state
	ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
	modui::set_screen_density(0.70625f);
	// modui::set_ui_scale(1.1f);
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
