cmake_minimum_required(VERSION 3.19)
################################################################################
project(JASS
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
	Widgets
	Quick
	REQUIRED
)
qt_standard_project_setup(REQUIRES 6.5)

set(PROJECT_SOURCES
	main.cpp
	resources.qrc
)

add_subdirectory(JASSView)
add_subdirectory(JASSCore)
add_subdirectory(JASSDemo)

################################################################################
qt_add_executable(JASS ${PROJECT_SOURCES})
################################################################################

qt_add_qml_module(JASS
	URI JASSComponents
	VERSION 1.0
	QML_FILES
	main.qml
)

target_link_libraries(JASS PRIVATE
	Qt6::Core
	Qt6::Widgets
	Qt6::Quick
)
################################################################################
