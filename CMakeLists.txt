cmake_minimum_required(VERSION 3.19)

project(JAS LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(alsa-lib asound)
find_package(Qt6 COMPONENTS
	Core
	Quick
	Concurrent
	REQUIRED)

qt_add_executable(JAS
	main.cpp
	organ.h organ.cpp
	generator.h generator.cpp
	sinegenerator.h sinegenerator.cpp
	resources.qrc
	)
set_target_properties(JAS PROPERTIES
	QT_QML_MODULE_VERSION 1.0
	QT_QML_MODULE_URI Music)
qt_qml_type_registration(JAS)
target_link_libraries(JAS PRIVATE
	${alsa-lib}
	Qt6::Core
	Qt6::Quick
	Qt6::Concurrent
	)
