#-------------------------------------------------
#
# Project created by QtCreator 2016-03-07T11:19:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MakeAmericaGreatAgain
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES +=\
        maga.cpp \
    frontend/MainFrame.cpp \
    frontend/LayeredWidget.cpp \
    backend/ResourceProvider.cpp \
    backend/Input.cpp \
    backend/GameCoordinator.cpp \
    frontend/TitleWidget.cpp \
    frontend/OfficeWidget.cpp

HEADERS  += frontend/MainFrame.h \
    frontend/LayeredWidget.h \
    backend/ResourceProvider.h \
    backend/Input.h \
    backend/GameCoordinator.h \
    frontend/TitleWidget.h \
    frontend/OfficeWidget.h

FORMS    += frontend/MainFrame.ui \
    frontend/TitleWidget.ui \
    frontend/OfficeWidget.ui


# Define copy command for linux and windows
QMAKE_COPY = cp -rf
Win32:QMAKE_COPY = copy /y

# cp(src, dest) returns the copy command
defineReplace(cp) {
    SDIR = $$PWD/$$1
    DDIR = $$OUT_PWD/$$2

    # Replace slashes in paths with backslashes for Windows
    win32:DDIR ~= s,/,\\,g
    win32:SDIR ~= s,/,\\,g

    return($$QMAKE_COPY $$SDIR $$DDIR;)
}

#Directorys to create
DIRS = img

#Loop over all given directories and append
#the build directory to make absolute paths
for(DIR, DIRS) {

     #append directorys to base dir
     mkcommands += $$OUT_PWD/$$DIR
}

#make a custom createDir variable with
#the command mkdir path1 path2 path3 ...
createDirs.commands = $(MKDIR) $$mkcommands

cpFiles.commands += $$cp(resources.txt, ./)
cpFiles.commands += $$cp(img/*, img/)

#Add dependencies to first
first.depends += createDirs
first.depends += cpFiles

#add dependencies to makefile
QMAKE_EXTRA_TARGETS += first createDirs cpFiles
