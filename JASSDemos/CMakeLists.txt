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
	resources.qrc
)
set(PROJECT_SHADERS
	darken.frag
  )
source_group(Shaders FILES ${PROJECT_SHADERS})
set(MODULE_SOURCES
)

set(MODULE_QML
	main.qml
	WhiteKey.qml
)
qt_add_executable(JASSDemos
	${PROJECT_SOURCES}
	${PROJECT_SHADERS}
)
qt_add_qml_module(JASSDemos
	URI JASSBasicDemo
	VERSION 1.0
	QML_FILES
	    Basic/main.qml
		Basic/BasicKey.qml
		Basic/Keyboard.qml
		Basic/ModeSelector.qml
		Basic/PlaybackControl.qml
		Basic/IconButton.qml
		Basic/RecordingSlicer.qml
		Basic/DynamicOrgan.qml
		Basic/decaySine.qml
		Basic/decaySquare.qml
		Basic/decayTriangle.qml
		Basic/testBed.qml
)
qt_add_shaders(JASSDemos "JASSDemos_shaders"
	PREFIX "/shaders"
	FILES ${PROJECT_SHADERS})
target_link_libraries(JASSDemos PRIVATE
	Qt::Core
	Qt::Concurrent
	Qt::Widgets
	JASSCoreplugin
	JASSViewplugin
)
