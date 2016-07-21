CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += \
    main.cc \
    game.cc \
    level.cc \
    player.cc \
    screen.cc \
    obstacle.cc
    game.cc
    level.cc
    player.cc
    screen.cc

HEADERS += \
    utils.hh \
    game.hh \
    level.hh \
    player.hh \
    screen.hh \
    obstacle.hh
    game.hh
    level.hh
    player.hh
    screen.hh

DISTFILES += \
    resources/info0 \
    resources/shader \
    resources/info1

FORMS +=


