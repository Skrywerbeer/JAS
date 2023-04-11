cmake_minimum_required(VERSION 3.19)
################################################################################
project(JASSSoundLibraryDemo
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

set(MODULE_SOURCES
)

set(MODULE_QML
	main.qml
)
source_group(QML FILES ${MODULE_QML})

qt_add_library(soundLibraryDemo STATIC)
qt_add_qml_module(soundLibraryDemo
	URI JASSDemo.SoundLibrary
	VERSION 1.0
	QML_FILES ${MODULE_QML}
	SOURCES ${MODULE_SOURCES}
)
