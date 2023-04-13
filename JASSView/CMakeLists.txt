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
	REQUIRED
)
qt_standard_project_setup(REQUIRES 6.5)

set(MODULE_SOURCES
	recordinggraph.h recordinggraph.cpp
	padding.h padding.cpp
	linegraph.h linegraph.cpp
	# Add nodes here for now.
	interval.h interval.cpp

	linesegmentnode.h linesegmentnode.cpp

	axis.h axis.cpp
	axisticks.h axisticks.cpp
	axisnode.h axisnode.cpp

	plot.h plot.cpp
	plotnode.h plotnode.cpp
)
set(MODULE_QML
	
)

qt_add_library(JASSView SHARED)

target_link_libraries(JASSView PRIVATE
	Qt::Core
	Qt::Quick

	JASSCore
)

qt_add_qml_module(JASSView
	URI JASSView
	VERSION 1.0
	QML_FILES ${MODULE_QML}
	SOURCES ${MODULE_SOURCES}
)
