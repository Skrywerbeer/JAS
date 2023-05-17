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

set(OSCILLATOR_HEADER_FILES
	oscillator.h
	sineoscillator.h
	triangleoscillator.h
	squareoscillator.h

	karplusstrong.h

	vco.h
	sinevco.h
	trianglevco.h
	squarevco.h
)
source_group("Oscillators/Header files" FILES ${OSCILLATOR_HEADER_FILES})
set(OSCILLATOR_SOURCE_FILES
	oscillator.cpp
	sineoscillator.cpp
	triangleoscillator.cpp
	squareoscillator.cpp

	karplusstrong.cpp

	vco.cpp
	sinevco.cpp
	trianglevco.cpp
	squarevco.cpp
)
source_group("Oscillators/Source files" FILES ${OSCILLATOR_SOURCE_FILES})
set(FUNCTIONS_HEADER_FILES
	constant.h
	adsr.h
	whitenoise.h
	exponential.h
)
source_group("Functions/Header files" FILES ${FUNCTIONS_HEADER_FILES})
set(FUNCTIONS_SOURCE_FILES
	constant.cpp
	adsr.cpp
	whitenoise.cpp
	exponential.cpp
)
source_group("Functions/Source files" FILES ${FUNCTIONS_SOURCE_FILES})
set(EFFECTS_HEADER_FILES
	amplifier.h
	effect.h
	decay.h
	delay.h
)
source_group("Effects/Header files" FILES ${EFFECTS_HEADER_FILES})
set(EFFECTS_SOURCE_FILES
	amplifier.cpp
	effect.cpp
	decay.cpp
	delay.cpp
)
source_group("Effects/Source files" FILES ${EFFECTS_SOURCE_FILES})


set(MODULE_SOURCES
  	jass.h
	jassplayer.h jassplayer.cpp
	source.h source.cpp
	patchboard.h patchboard.cpp
	mixer.h mixer.cpp
	audiorecording.h audiorecording.cpp
	${FUNCTIONS_HEADER_FILES} ${FUNCTIONS_SOURCE_FILES}
	${OSCILLATOR_HEADER_FILES} ${OSCILLATOR_SOURCE_FILES}
	${EFFECTS_HEADER_FILES} ${EFFECTS_SOURCE_FILES}
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
