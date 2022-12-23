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
	Quick
	REQUIRED)

set(MODULE_SOURCES
	recordinggraph.h recordinggraph.cpp
)

set(MODULE_QML
	
)

qt_add_library(JASSView STATIC)

target_link_libraries(JASSView PRIVATE
	Qt::Core
	Qt::Quick
)

qt_add_qml_module(JASSView
	URI "JASSView"
	VERSION 1.0
	QML_FILES ${MODULE_QML}
	SOURCES ${MODULE_SOURCES}
)
