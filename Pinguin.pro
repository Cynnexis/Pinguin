#-------------------------------------------------
#
# Project created by QtCreator 2018-10-12T18:54:18
#
#-------------------------------------------------

QT       += core gui charts network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pinguin
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dsettings.cpp \
    ping.cpp \
	networkutility.cpp

HEADERS += \
        mainwindow.h \
    dsettings.h \
    ping.h \
	networkutility.h

FORMS += \
        mainwindow.ui \
    dsettings.ui

RESOURCES += \
	resources.qrc

RC_FILE = pinguin.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    .gitignore \
    compile_res.bat \
    pinguin.rc

test {
	message(Test build)
	QT += testlib
	TARGET = UnitTests

	HEADERS -= mainwindow.h

	SOURCES -= main.cpp \
		mainwindow.cpp

	HEADERS += test/networkutilitytestcase.h

	SOURCES += test/main.cpp \
		test/networkutilitytestcase.cpp
} else {
	message(Normal build)
}
