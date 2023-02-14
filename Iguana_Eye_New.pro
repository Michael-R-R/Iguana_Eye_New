CONFIG += c++17

QT += core gui
QT += opengl
QT += widgets
QT += openglwidgets

include(Iguana_Eye_New.pri)

SOURCES += $$files(src/*.cpp, true)
HEADERS += $$files(src/*.h, true)
RESOURCES += $$files(resources/*.qrc, true)
FORMS += $$files(forms/*.ui, true)
UI_DIR += $$PWD/forms/headers

LIBS += -L$$PWD/required/libs/Assimp/ -lassimp-vc142-mtd
LIBS += -L$$PWD/required/libs/Assimp/ -lassimp-vc142-mt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
