CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(daniel_zeichensaetze)

FIND_PACKAGE(Qt4 REQUIRED)

SET(daniel_zeichensaetze_SOURCES main.cpp DzMainClass.cpp DzCopyer.cpp)
SET(daniel_zeichensaetze_HEADERS DzMainClass.hpp DzCopyer.hpp)
QT4_WRAP_CPP(daniel_zeichensaetze_HEADERS_MOC ${daniel_zeichensaetze_HEADERS})

INCLUDE(${QT_USE_FILE})

ADD_DEFINITIONS(${QT_DEFINITIONS})

ADD_EXECUTABLE(daniel_zeichensaetze ${daniel_zeichensaetze_SOURCES} ${daniel_zeichensaetze_HEADERS_MOC})

TARGET_LINK_LIBRARIES(daniel_zeichensaetze ${QT_LIBRARIES})
