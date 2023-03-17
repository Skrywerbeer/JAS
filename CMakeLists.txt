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
	Concurrent
	ShaderTools
	REQUIRED
)

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

add_subdirectory(JASSView)
add_subdirectory(JASSCore)
add_subdirectory(JASSDemo)

if (ANDROID)
	list(APPEND PROJECT_SOURCES ${ANDROID_FILES} ${ANDROID_JAVA})
endif()
################################################################################
qt_add_executable(JASS ${PROJECT_SOURCES})
################################################################################
if (ANDROID)
	target_include_directories(JASS PUBLIC "oboe/include")
	set_target_properties(JASS PROPERTIES
		QT_ANDROID_PACKAGE_SOURCE_DIR ${ANDROID_DIR}
		QT_ANDROID_VERSION_NAME ${ANDROID_VERSION_NAME}
		QT_ANDROID_VERSION_CODE ${ANDROID_VERSION_CODE})
endif()

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
	Qt6::Concurrent

)
################################################################################
