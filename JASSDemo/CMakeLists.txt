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
	ShaderTools
	REQUIRED
)
qt_standard_project_setup(REQUIRES 6.5)

if(ANDROID)
	set(ANDROID_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
	set(ANDROID_FILES
		${ANDROID_DIR}/gradle.properties
		${ANDROID_DIR}/build.gradle
		${ANDROID_DIR}/AndroidManifest.xml
#		${ANDROID_DIR}/res/values/styles.xml
#		${ANDROID_DIR}/res/drawable/splash.xml
    )
    source_group(Android FILES ${ANDROID_FILES})
	set(ANDROID_JAVA
		${ANDROID_DIR}/src/org/skrywerbeer/MainActivity.java
	    )
	source_group(Java FILES ${ANDROID_JAVA})
	set(ANDROID_VERSION_NAME ${CMAKE_PROJECT_VERSION})
	set(ANDROID_VERSION_CODE 1)
endif()

set(PROJECT_SOURCES
	main.cpp
	resources.qrc
)
set(PROJECT_SHADERS
	darken.frag
	glow.frag glow.vert
	borderblur.frag
)
source_group(Shaders FILES ${PROJECT_SHADERS})

set(MODULE_SOURCES
)
set(MODULE_QML
	Main.qml

	DemoModel.qml
)
source_group(QML FILES ${MODULE_QML})

add_subdirectory(Basic)
add_subdirectory(Piano)
add_subdirectory(SoundLibrary)

if (ANDROID)
	list(APPEND PROJECT_SOURCES ${ANDROID_FILES} ${ANDROID_JAVA})
endif()


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

if (ANDROID)
#	target_include_directories(JASS PUBLIC "oboe/include")
    set_target_properties(JASSDemo PROPERTIES
		QT_ANDROID_PACKAGE_SOURCE_DIR ${ANDROID_DIR}
		QT_ANDROID_VERSION_NAME ${ANDROID_VERSION_NAME}
		QT_ANDROID_VERSION_CODE ${ANDROID_VERSION_CODE})
endif()

target_link_libraries(JASSDemo PRIVATE
	Qt::Core
	Qt::Widgets
	JASSCore
	JASSView

	basicDemo
	pianoDemo
	soundLibraryDemo
)
