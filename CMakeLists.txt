cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME modui)
project(${PROJECT_NAME})

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(MODUI_LIB_NAME "modui")
set(MODUI_DEMO_EXE_NAME "modui_demo")
set(MODUI_ICONS_PATH assets/icons) # must be relative to ${CMAKE_SOURCE_DIR}

option(MODUI_BUILD_DEMO "Build demo executable" ON)
option(MODUI_EMBED_ICONS "Build lib with icons" ON)

if (MODUI_EMBED_ICONS)
	add_compile_definitions(MODUI_EMBED_ICONS=1)
endif()

set(MODUI_SRC
	include/stb/stb_image.cpp

	include/modui/core/image/image.cxx
	include/modui/core/image/rasterimage.cxx
	include/modui/core/image/selectableimage.cxx
	include/modui/core/image/vectoricon.cxx
	include/modui/core/image/vectorimage.cxx

	include/modui/core/common.cxx
	include/modui/core/exceptions.cxx

	include/modui/internal/internal_core.cxx
	include/modui/internal/internal_utils.cxx

	include/modui/ui/button/basebutton.cxx
	include/modui/ui/button/button.cxx
	include/modui/ui/button/iconbutton.cxx

	include/modui/ui/card/card.cxx

	include/modui/ui/checkbox/checkbox.cxx

	include/modui/ui/layout/linearlayout.cxx
	include/modui/ui/layout/scrolllayout.cxx

	include/modui/ui/list/listitem.cxx

	include/modui/ui/screen/screen.cxx
	include/modui/ui/screen/screenmanager.cxx

	include/modui/ui/slider/baseslider.cxx
	include/modui/ui/slider/slider.cxx

	include/modui/ui/switch/switch.cxx

	include/modui/ui/text/text.cxx

	include/modui/ui/widget.cxx

	include/modui/icons.cxx
	include/modui/theme.cxx
	include/modui/app.cxx
)

add_library( ${MODUI_LIB_NAME} SHARED
	${MODUI_SRC}
)

target_link_libraries( ${MODUI_LIB_NAME}
	imgui
	opengl32.lib
	d3dcompiler
	dwmapi
)

if (MODUI_BUILD_DEMO)
	# Windows only!

	add_executable( ${MODUI_DEMO_EXE_NAME}
		demo.cxx
	)

	target_link_libraries( ${MODUI_DEMO_EXE_NAME}
		${MODUI_LIB_NAME}
	)

	add_custom_command(
		TARGET ${MODUI_DEMO_EXE_NAME} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/libimgui.dll .
	)
endif()
