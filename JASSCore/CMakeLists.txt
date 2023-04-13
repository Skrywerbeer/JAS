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
	Widgets
	Concurrent
	REQUIRED
)
qt_standard_project_setup(REQUIRES 6.5)

if(ANDROID)
	add_subdirectory("oboe")
else ()
	find_library(alsa-lib asound)
endif()

set(MODULE_SOURCES
  	jass.h
	jassplayer.h jassplayer.cpp
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
	patchboard.h patchboard.cpp
	mixer.h mixer.cpp
	vca.h vca.cpp
	vco.h vco.cpp
	sinevco.h sinevco.cpp
	trianglevco.h trianglevco.cpp
	squarevco.h squarevco.cpp
	audiorecording.h audiorecording.cpp
)
set(MODULE_QML
	
)

qt_add_library(JASSCore SHARED)
qt_add_qml_module(JASSCore
	URI JASSCore
	VERSION 1.0
	QML_FILES ${MODULE_QML}
	SOURCES ${MODULE_SOURCES}
)

target_link_libraries(JASSCore PRIVATE
	Qt::Core
	Qt::Concurrent
)
if (ANDROID)
	target_link_libraries(JASSCore PRIVATE oboe)
else()
	target_link_libraries(JASSCore PRIVATE ${alsa-lib})
endif()
