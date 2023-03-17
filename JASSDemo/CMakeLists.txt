cmake_minimum_required(VERSION 3.19)
################################################################################
project(JASSDemo
	LANGUAGES CXX
	VERSION 0.4)
################################################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS
	Core
	Quick
	Widgets
	Concurrent
	REQUIRED
)

set(PROJECT_SOURCES
	main.cpp
	resources.qrc
)
set(PROJECT_SHADERS
	darken.frag
)
source_group(Shaders FILES ${PROJECT_SHADERS})

set(MODULE_SOURCES
)
set(MODULE_QML
)

add_subdirectory(Basic)
add_subdirectory(Piano)


qt_add_executable(JASSDemo
	${PROJECT_SOURCES}
	${PROJECT_SHADERS}
)
qt_add_qml_module(JASSDemo
	URI JASSDemoComponents
	VERSION 1.0
	QML_FILES ${MODULE_QML}
)
qt_add_shaders(JASSDemo "JASSDemos_shaders"
	PREFIX "/shaders"
	FILES ${PROJECT_SHADERS})

target_link_libraries(JASSDemo PRIVATE
	Qt::Core
	Qt::Concurrent
	Qt::Widgets

	JASSCoreplugin
	JASSViewplugin

	basicDemoplugin
	pianoDemoplugin
)
