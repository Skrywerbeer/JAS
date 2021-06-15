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

set(QT_VERSION_MAJOR 6)
set(QT_DEFAULT_MAJOR_VERSION 6)

find_package(Qt6 COMPONENTS
	Core
	Widgets
	Quick
	Concurrent
	ShaderTools
	REQUIRED)

if(ANDROID)
	add_subdirectory("oboe")
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
else ()
	find_library(alsa-lib asound)
endif()

set(PROJECT_SOURCES
	main.cpp
	jass.h
	organ.h organ.cpp
	source.h source.cpp
	constant.h constant.cpp
	adsr.h adsr.cpp
	whitenoise.h whitenoise.cpp
	oscillator.h oscillator.cpp
	sineoscillator.h sineoscillator.cpp
	triangleoscillator.h triangleoscillator.cpp
	squareoscillator.h squareoscillator.cpp
	effect.h effect.cpp
	decay.h decay.cpp
	delay.h delay.cpp
	splitter.h splitter.cpp
	mixer.h mixer.cpp
	vca.h vca.cpp
	vco.h vco.cpp
	sinevco.h sinevco.cpp
	trianglevco.h trianglevco.cpp
	squarevco.h squarevco.cpp
	audiorecording.h audiorecording.cpp
	recordinggraph.h recordinggraph.cpp
	resources.qrc
	)
set(PROJECT_SHADERS
	darken.frag
	)
source_group(Shaders FILES ${PROJECT_SHADERS})
if (ANDROID)
	list(APPEND PROJECT_SOURCES ${ANDROID_FILES} ${ANDROID_JAVA})
endif()
################################################################################
qt_add_executable(JASS ${PROJECT_SOURCES} ${PROJECT_SHADERS})
################################################################################
if (ANDROID)
	target_include_directories(JASS PUBLIC "oboe/include")
	set_target_properties(JASS PROPERTIES
		QT_ANDROID_PACKAGE_SOURCE_DIR ${ANDROID_DIR}
		QT_ANDROID_VERSION_NAME ${ANDROID_VERSION_NAME}
		QT_ANDROID_VERSION_CODE ${ANDROID_VERSION_CODE})
endif()

set_target_properties(JASS PROPERTIES
	QT_QML_MODULE_VERSION 1.0
	QT_QML_MODULE_URI JASS)
qt_qml_type_registration(JASS)
qt_add_shaders(JASS "JASS_shaders"
	PREFIX "/shaders"
	FILES ${PROJECT_SHADERS})
target_link_libraries(JASS PRIVATE
	Qt6::Core
	Qt6::Widgets
	Qt6::Quick
	Qt6::Concurrent
	)
if (ANDROID)
	target_link_libraries(JASS PRIVATE oboe)
else()
	target_link_libraries(JASS PRIVATE ${alsa-lib})
endif()
################################################################################
