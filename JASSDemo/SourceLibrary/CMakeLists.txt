cmake_minimum_required(VERSION 3.19)
################################################################################
project(JASSSourceLibraryDemo
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
qt_standard_project_setup(REQUIRES 6.5)

set(MODULE_SOURCES
)

set(MODULE_QML
	Main.qml
	LibraryCard.qml
	SpinBox.qml
	ParameterControl.qml

	LibraryModel.qml
)
source_group(QML FILES ${MODULE_QML})
set(MODULE_JS

)
source_group(JS FILES ${MODULE_JS})


qt_add_library(sourceLibraryDemo SHARED)
qt_add_qml_module(sourceLibraryDemo
	URI JASSDemo.SourceLibrary
	VERSION 1.0
	QML_FILES ${MODULE_QML}
	SOURCES ${MODULE_SOURCES}
	RESOURCES ${MODULE_JS}
)
