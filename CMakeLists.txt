cmake_minimum_required(VERSION 2.6)

project(
	daniel_zeichensaetze)

find_package(Qt4 REQUIRED)

set(
	daniel_zeichensaetze_SOURCES
	main.cpp
	DzMainClass.cpp
	DzCopyer.cpp)

set(
	daniel_zeichensaetze_HEADERS
	DzMainClass.hpp
	DzCopyer.hpp)

QT4_WRAP_CPP(
	daniel_zeichensaetze_HEADERS_MOC
	${daniel_zeichensaetze_HEADERS})

include(
	${QT_USE_FILE})

add_definitions(
	${QT_DEFINITIONS})

add_executable(
	daniel_zeichensaetze
	WIN32
	${daniel_zeichensaetze_SOURCES}
	${daniel_zeichensaetze_HEADERS_MOC})

TARGET_LINK_LIBRARIES(
	daniel_zeichensaetze
	${QT_QTMAIN_LIBRARY}
	${QT_LIBRARIES})
