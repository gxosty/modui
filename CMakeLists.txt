cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src/modui/internal)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(PROJECT_NAME modui)
set(MODUI_LIB_NAME modui)
set(MODUI_DEMO_EXE_NAME modui_demo)

option(MODUI_BUILD_DEMO "Build demo executable" ON)

add_definitions(-DMODUI_BACKEND_SDL2)

project(${PROJECT_NAME})

add_library( ${MODUI_LIB_NAME} SHARED
	src/modui/core/common.cxx
	src/modui/core/exceptions.cxx

	src/modui/internal/internal_core.cxx
	src/modui/internal/internal_utils.cxx

	src/modui/ui/button/basebutton.cxx
	src/modui/ui/button/button.cxx

	src/modui/ui/checkbox/checkbox.cxx

	src/modui/ui/layout/linearlayout.cxx

	src/modui/ui/screen/screen.cxx
	src/modui/ui/screen/screenmanager.cxx

	src/modui/ui/slider/baseslider.cxx
	src/modui/ui/slider/slider.cxx

	src/modui/ui/text/text.cxx

	src/modui/ui/widget.cxx

	src/modui/theme.cxx
	src/modui/app.cxx
)

target_link_libraries( ${MODUI_LIB_NAME}
	imgui
	dl
	SDL2
	GL
)

if (MODUI_BUILD_DEMO)
	add_executable( ${MODUI_DEMO_EXE_NAME}
		src/demo.cxx
	)

	target_link_libraries( ${MODUI_DEMO_EXE_NAME}
		${MODUI_LIB_NAME}
	)
endif()