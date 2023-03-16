cmake_minimum_required(VERSION 3.19)
################################################################################
project(JASSDemos
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
	REQUIRED)

set(PROJECT_SOURCES
	main.cpp
)

set(MODULE_SOURCES
)

set(MODULE_QML
	main.qml
	WhiteKey.qml
)
qt_add_executable(JASSDemos
	${PROJECT_SOURCES}
)
qt_add_qml_module(JASSDemos
	URI JASSDemosComponents
	VERSION 1.0
	QML_FILES ${MODULE_QML}
	SOURCES ${MODULE_SOURCES}
)
target_link_libraries(JASSDemos PRIVATE
	Qt::Core
	Qt::Concurrent
	Qt::Widgets
)
