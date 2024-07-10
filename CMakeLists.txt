cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME modui)
project(${PROJECT_NAME})

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src/modui/internal)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(MODUI_LIB_NAME modui)
set(MODUI_DEMO_EXE_NAME modui_demo)

option(MODUI_BUILD_DEMO "Build demo executable" ON)

add_library( ${MODUI_LIB_NAME} SHARED
	include/stb/stb_image.cpp

	src/modui/core/image/image.cxx
	src/modui/core/image/rasterimage.cxx

	src/modui/core/common.cxx
	src/modui/core/exceptions.cxx

	src/modui/internal/internal_core.cxx
	src/modui/internal/internal_utils.cxx

	src/modui/ui/button/basebutton.cxx
	src/modui/ui/button/button.cxx
	src/modui/ui/button/iconbutton.cxx

	src/modui/ui/card/card.cxx

	src/modui/ui/checkbox/checkbox.cxx

	src/modui/ui/layout/linearlayout.cxx
	src/modui/ui/layout/scrolllayout.cxx

	src/modui/ui/screen/screen.cxx
	src/modui/ui/screen/screenmanager.cxx

	src/modui/ui/slider/baseslider.cxx
	src/modui/ui/slider/slider.cxx

	src/modui/ui/switch/switch.cxx

	src/modui/ui/text/text.cxx

	src/modui/ui/widget.cxx

	src/modui/theme.cxx
	src/modui/app.cxx
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
		src/demo.cxx
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
