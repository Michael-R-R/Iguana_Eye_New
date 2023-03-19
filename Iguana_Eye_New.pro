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

CONFIG(debug, debug|release)
{
    LIBS += -L$$PWD/required/libs/Assimp/ -lassimp-vc142-mtd
    LIBS += -L$$PWD/required/libs/Lua/ -llua-5.4.4
    LIBS += -L$$PWD/required/libs/Physx/debug/ -lPhysX_64
    LIBS += -L$$PWD/required/libs/Physx/debug/ -lPhysXCommon_64
    LIBS += -L$$PWD/required/libs/Physx/debug/ -lPhysXCooking_64
    LIBS += -L$$PWD/required/libs/Physx/debug/ -lPhysXExtensions_static_64
    LIBS += -L$$PWD/required/libs/Physx/debug/ -lPhysXFoundation_64
}
CONFIG(release, debug|release)
{
    LIBS += -L$$PWD/required/libs/Assimp/ -lassimp-vc142-mt
    LIBS += -L$$PWD/required/libs/Lua/ -llua-5.4.4
    LIBS += -L$$PWD/required/libs/Physx/release/ -lPhysX_64
    LIBS += -L$$PWD/required/libs/Physx/release/ -lPhysXCommon_64
    LIBS += -L$$PWD/required/libs/Physx/release/ -lPhysXCooking_64
    LIBS += -L$$PWD/required/libs/Physx/release/ -lPhysXExtensions_static_64
    LIBS += -L$$PWD/required/libs/Physx/release/ -lPhysXFoundation_64
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
