cmake_minimum_required(VERSION 3.19)
################################################################################
project(BasicDemo
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
)
set(MODULE_QML
    main.qml
	BasicKey.qml
	Keyboard.qml
	ModeSelector.qml
	PlaybackControl.qml
	IconButton.qml
	RecordingSlicer.qml
	DynamicOrgan.qml
	DecaySine.qml
	DecaySquare.qml
	DecayTriangle.qml
	StrangeReed.qml
)
source_group(QML FILES ${MODULE_QML})

qt_add_library(basicDemo SHARED)
qt_add_qml_module(basicDemo
	URI JASSDemo.Basic
	VERSION 1.0
	QML_FILES ${MODULE_QML}
)
