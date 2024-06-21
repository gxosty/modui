#include <modui/app.hpp>
#include <modui/ui/screen/screen.hpp>
#include <modui/ui/screen/screenmanager.hpp>
#include <modui/ui/layout/linearlayout.hpp>
#include <modui/ui/button/button.hpp>
#include <modui/ui/slider/slider.hpp>
#include <modui/ui/checkbox/checkbox.hpp>
#include <modui/ui/text/text.hpp>

#include <imgui/imgui.h>

#include <iostream>
#include <cmath>

namespace ui = modui::ui;

class CustomWidget : public ui::LinearLayout
{
public:
	CustomWidget() : ui::LinearLayout(modui::LAYOUT_ORIENTATION_VERTICAL), count{0} {}

	static CustomWidget* init()
	{
		return MODUI_WIDGET_INIT(CustomWidget);
	}

	void update()
	{
		this->text->set_text("Count: " + std::to_string(this->count));
	}

private:
	virtual void on_create_widget() override
	{
		this->add_widget(
			ui::Text::init("Count: 0")
				->set_id("text")
		)
		->add_widget(
			ui::Button::init("Add +1")
				->on_release(MODUI_CALLBACK(this) {
					this->count++;
					this->update();
				})
		);

		text = (ui::Text*)this->find_widget_by_id("text");
	}

	int count;
	ui::Text* text;
};

class MyApp : public modui::App
{
public:
	MyApp() : modui::App("MyApp") {}

	virtual ui::Widget* build() override
	{
		this->screen_manager = ui::ScreenManager::init();

		return
		this->screen_manager
			->add_widget(
				ui::Screen::init("screen1")
					->add_widget(
						ui::LinearLayout::init()
							->set_spacing(DP(10))
							->add_widget(
								ui::LinearLayout::init(modui::LAYOUT_ORIENTATION_HORIZONTAL)
									->set_spacing(DP(5))
									->add_widget(
										ui::Text::init("0.0000000")
											->set_id("slider_value")
											->set_size_y(DP(20))
									)
									->add_widget(
										ui::Slider::init(0.0f, 100.0f)
											->on_slide(MODUI_CALLBACK(this) {
												ui::Text* text = (ui::Text*)this->screen_manager->find_widget_by_id("slider_value");
												ui::Slider* slider = (ui::Slider*)this_widget;
												slider->set_value(round(slider->get_value()));
												text->set_text(std::to_string(slider->get_value()));
											})
									)
							)
							->add_widget(
								ui::Text::init("You are currently in screen1")
							)
							->add_widget(
								ui::Checkbox::init()
							)
							->add_widget(
								ui::Button::init("Change to screen1")
									->on_release(MODUI_CALLBACK(this) {
										this->screen_manager->set_screen("screen2");
									})
							)
							->add_widget(
								CustomWidget::init()
							)
							->add_widget(
								CustomWidget::init()
							)
					)
			)
			->add_widget(
				ui::Screen::init("screen2")
					->add_widget(
						ui::LinearLayout::init()
							->add_widget(
								ui::Text::init("Now you are in screen2")
							)
							->add_widget(
								ui::Button::init("Change to screen1")
									->on_release(MODUI_CALLBACK(this) {
										this->screen_manager->set_screen("screen1");
									})
							)
					)
			);
	}

private:
	ui::ScreenManager* screen_manager;
};

int main()
{
	MyApp* app = new MyApp();
	app->run();
	delete app;

	return 0;
}