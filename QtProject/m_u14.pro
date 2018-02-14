
TEMPLATE = aux
CONFIG -= console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
TARGET = UE4

# All the defines of your project will go in this file

include(defines.pri)

# Qt Creator will automatically add headers and source files if you add them via Qt Creator.

HEADERS += ../Source/m_u14/m_u14.h \
../Source/m_u14/m_u14GameModeBase.h \ 
    ../Source/m_u14/m_u14_GameMode.h \
    ../Source/m_u14/Geometer.h \
    ../Source/m_u14/Algebra.h \
    ../Source/m_u14/Colorz.h \
    ../Source/m_u14/SubGameTimer.h \
    ../Source/m_u14/m_u14_Hud.h \
    ../Source/m_u14/Walker_CH.h \
    ../Source/m_u14/Walker_AI.h \
    ../Source/m_u14/MyCharacter.h \
    ../Source/m_u14/MyAIController.h

SOURCES += ../Source/m_u14/m_u14.cpp \
../Source/m_u14/m_u14GameModeBase.cpp \ 
    ../Source/m_u14/m_u14_GameMode.cpp \
    ../Source/m_u14/Geometer.cpp \
    ../Source/m_u14/Algebra.cpp \
    ../Source/m_u14/Colorz.cpp \
    ../Source/m_u14/SubGameTimer.cpp \
    ../Source/m_u14/Hud.cpp \
    ../Source/m_u14/m_u14_Hud.cpp \
    ../Source/m_u14/Walker_CH.cpp \
    ../Source/m_u14/Walker_AI.cpp \
    ../Source/m_u14/MyCharacter.cpp \
    ../Source/m_u14/MyAIController.cpp

# All your generated includes will go in this file

include(includes.pri)

DISTFILES +=../Source/m_u14/m_u14.Build.cs 

