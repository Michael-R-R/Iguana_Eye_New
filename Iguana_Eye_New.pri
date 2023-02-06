INCLUDEPATH += $$PWD/required/include

INCLUDEPATH += $$PWD/src/Application \
    $$PWD/src/Application/ApplicationWindow

INCLUDEPATH += $$PWD/src/Editor \
    $$PWD/src/Editor/EditorActionManager \
    $$PWD/src/Editor/EditorInput \

INCLUDEPATH += $$PWD/src/Editor/EditorUi \
    $$PWD/src/Editor/EditorUi/MainMenuBar \
    $$PWD/src/Editor/EditorUi/EditorWindowManager \
    $$PWD/src/Editor/EditorUi/StatusBar

INCLUDEPATH += $$PWD/src/Editor/Widgets \
    $$PWD/src/Editor/Widgets/CollapsingHeader

INCLUDEPATH += $$PWD/src/Editor/Widgets/AppOptionsWidgets \
    $$PWD/src/Editor/Widgets/AppOptionsWidgets/EditorHotkeyTableWidget \
    $$PWD/src/Editor/Widgets/AppOptionsWidgets/FetchUserInputWidget \
    $$PWD/src/Editor/Widgets/AppOptionsWidgets/GameHotkeyTableWidget \
    $$PWD/src/Editor/Widgets/AppOptionsWidgets/HotkeyTableWidget \
    $$PWD/src/Editor/Widgets/AppOptionsWidgets/SelectAppOptionsWidget

INCLUDEPATH += $$PWD/src/Editor/Actions/ \
    $$PWD/src/Editor/Actions/AppOptionsAction \
    $$PWD/src/Editor/Actions/LoadGameAction \
    $$PWD/src/Editor/Actions/MenuAction \
    $$PWD/src/Editor/Actions/QuitAppAction \
    $$PWD/src/Editor/Actions/SaveAsGameAction \
    $$PWD/src/Editor/Actions/SaveGameAction \
    $$PWD/src/Editor/Actions/ToggleGameRenderAction \
    $$PWD/src/Editor/Actions/ToggleGameUpdateAction \
    $$PWD/src/Editor/Actions/ToggleUiAction

INCLUDEPATH += $$PWD/src/Editor/Menus \
    $$PWD/src/Editor/Menus/FileSubMenu \
    $$PWD/src/Editor/Menus/GameSubMenu \
    $$PWD/src/Editor/Menus/SubMenu

INCLUDEPATH += $$PWD/src/Editor/Windows \
    $$PWD/src/Editor/Windows/AppOptionsWindow

INCLUDEPATH += $$PWD/src/Events \
    $$PWD/src/Events/AppStartEvent

INCLUDEPATH += $$PWD/src/Game \
    $$PWD/src/Game/IEBuffer \
    $$PWD/src/Game/IEObject \
    $$PWD/src/Game/IEScene \
    $$PWD/src/Game/IEUniform

INCLUDEPATH += $$PWD/src/Game/IEResources \
    $$PWD/src/Game/IEResources/IEMaterial \
    $$PWD/src/Game/IEResources/IEMesh \
    $$PWD/src/Game/IEResources/IERenderable \
    $$PWD/src/Game/IEResources/IEResource \
    $$PWD/src/Game/IEResources/IEResourceContainer \
    $$PWD/src/Game/IEResources/IEShader

INCLUDEPATH += $$PWD/src/Game/Managers \
    $$PWD/src/Game/Managers/IEManager \
    $$PWD/src/Game/Managers/IEMaterialManager \
    $$PWD/src/Game/Managers/IEMeshManager \
    $$PWD/src/Game/Managers/IENameManager \
    $$PWD/src/Game/Managers/IERenderableManager \
    $$PWD/src/Game/Managers/IEShaderManager

INCLUDEPATH += $$PWD/src/Game/Systems \
    $$PWD/src/Game/Systems/IEInput

INCLUDEPATH += $$PWD/src/Game/Systems/IETime \
    $$PWD/src/Game/Systems/IETime/DeltaTime

INCLUDEPATH += $$PWD/src/Input \
    $$PWD/src/Input/InputContainer \
    $$PWD/src/Input/InputCapture \
    $$PWD/src/Input/InputKey

INCLUDEPATH += $$PWD/src/Utility \
    $$PWD/src/Utility/IEFile \
    $$PWD/src/Utility/IEHash \
    $$PWD/src/Utility/IESerialize
