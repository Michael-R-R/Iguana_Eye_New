INCLUDEPATH += $$PWD/required/include

INCLUDEPATH += $$PWD/src/Application \
    $$PWD/src/Application/ApplicationWindow

INCLUDEPATH += $$PWD/src/Application/Editor \
    $$PWD/src/Application/Editor/EditorActionManager \
    $$PWD/src/Application/Editor/EditorInput \
    $$PWD/src/Application/Editor/EditorUi \
    $$PWD/src/Application/Editor/EditorWindowManager

INCLUDEPATH += $$PWD/src/Application/Editor/Widgets \
    $$PWD/src/Application/Editor/Widgets/CollapsingHeader \
    $$PWD/src/Application/Editor/Widgets/MainMenuBar \
    $$PWD/src/Application/Editor/Widgets/StatusBar

INCLUDEPATH += $$PWD/src/Application/Editor/Widgets/AppOptionsWidgets \
    $$PWD/src/Application/Editor/Widgets/AppOptionsWidgets/EditorHotkeyTableWidget \
    $$PWD/src/Application/Editor/Widgets/AppOptionsWidgets/FetchUserInputWidget \
    $$PWD/src/Application/Editor/Widgets/AppOptionsWidgets/GameHotkeyTableWidget \
    $$PWD/src/Application/Editor/Widgets/AppOptionsWidgets/HotkeyTableWidget \
    $$PWD/src/Application/Editor/Widgets/AppOptionsWidgets/SelectAppOptionsWidget

INCLUDEPATH += $$PWD/src/Application/Editor/Widgets/MenuActions \
    $$PWD/src/Application/Editor/Widgets/MenuActions/AppOptionsAction \
    $$PWD/src/Application/Editor/Widgets/MenuActions/MenuAction \
    $$PWD/src/Application/Editor/Widgets/MenuActions/QuitAppAction \
    $$PWD/src/Application/Editor/Widgets/MenuActions/ToggleGameRenderAction \
    $$PWD/src/Application/Editor/Widgets/MenuActions/ToggleGameUpdateAction \
    $$PWD/src/Application/Editor/Widgets/MenuActions/ToggleUiAction

INCLUDEPATH += $$PWD/src/Application/Editor/Widgets/Menus \
    $$PWD/src/Application/Editor/Widgets/Menus/FileSubMenu \
    $$PWD/src/Application/Editor/Widgets/Menus/GameSubMenu \
    $$PWD/src/Application/Editor/Widgets/Menus/SubMenu

INCLUDEPATH += $$PWD/src/Application/Editor/Windows \
    $$PWD/src/Application/Editor/Windows/AppOptionsWindow

INCLUDEPATH += $$PWD/src/Application/Game

INCLUDEPATH += $$PWD/src/Application/Game/Systems \
    $$PWD/src/Application/Game/Systems/IEInput

INCLUDEPATH += $$PWD/src/Application/Game/Systems/IETime \
    $$PWD/src/Application/Game/Systems/IETime/DeltaTime

INCLUDEPATH += $$PWD/src/Application/Input \
    $$PWD/src/Application/Input/InputContainer \
    $$PWD/src/Application/Input/InputCapture \
    $$PWD/src/Application/Input/InputKey

INCLUDEPATH += $$PWD/src/Events \
    $$PWD/src/Events/AppStartEvent

INCLUDEPATH += $$PWD/src/IEObject \

INCLUDEPATH += $$PWD/src/Utility \
    $$PWD/src/Utility/IEFile \
    $$PWD/src/Utility/Serialize
