cmake_minimum_required(VERSION 3.19)
################################################################################
project(JASSPianoDemo
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
	textfile.cpp textfile.h
)

set(MODULE_QML
    main.qml
	Whitekey.qml
	Blackkey.qml
	Keyboard.qml
	Halo.qml

	SynthSound.qml

	Colors.qml

	SoundEditor.qml
)
source_group(QML FILES ${MODULE_QML})

set_source_files_properties(Colors.qml PROPERTIES
	QT_QML_SINGLETON_TYPE TRUE)
qt_add_library(pianoDemo SHARED)
qt_add_qml_module(pianoDemo
	URI JASSDemo.Piano
	VERSION 1.0
	QML_FILES ${MODULE_QML}
	SOURCES ${MODULE_SOURCES}
)
