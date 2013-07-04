#-------------------------------------------------
#
# Project created by QtCreator 2013-06-06T13:00:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TemplateParser
TEMPLATE = app


SOURCES += main.cpp\
        TemplateParserDlg.cpp \
    json.cpp

HEADERS  += TemplateParserDlg.h \
    psdparser.h \
    json.h

FORMS    += TemplateParserDlg.ui

CONFIG += debug_and_release

CONFIG(debug, debug|release)
{
    LIBS += -L ./debug -lpsdparser
}

CONFIG(release, debug|release)
{
    LIBS += -L./release -lpsdparser
}

OTHER_FILES += \
    README.md
