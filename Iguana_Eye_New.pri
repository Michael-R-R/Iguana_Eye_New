INCLUDEPATH += $$PWD/required/include \
INCLUDEPATH += $$PWD/required/include/lua \
INCLUDEPATH += $$PWD/required/include/physx \

INCLUDEPATH += $$PWD/src/Application \
    $$PWD/src/Application/ApplicationProperties \
    $$PWD/src/Application/ApplicationWindow \

INCLUDEPATH += $$PWD/src/Common \
    $$PWD/src/Common/IEObject \

INCLUDEPATH += $$PWD/src/Editor \

INCLUDEPATH += $$PWD/src/Editor/Actions \
    $$PWD/src/Editor/Actions/CompileShaderAction \
    $$PWD/src/Editor/Actions/BaseAction \
    $$PWD/src/Editor/Actions/NewGameFileAction \
    $$PWD/src/Editor/Actions/NewShaderAction \
    $$PWD/src/Editor/Actions/OpenGameFileAction \
    $$PWD/src/Editor/Actions/OpenShaderAction \
    $$PWD/src/Editor/Actions/QuitAppAction \
    $$PWD/src/Editor/Actions/SaveAsGameFileAction \
    $$PWD/src/Editor/Actions/SaveAsShaderAction \
    $$PWD/src/Editor/Actions/SaveGameFileAction \
    $$PWD/src/Editor/Actions/SaveShaderAction \
    $$PWD/src/Editor/Actions/ToggleEditorUiAction \
    $$PWD/src/Editor/Actions/ToggleGamePlayAction \
    $$PWD/src/Editor/Actions/ToggleGameRenderAction \
    $$PWD/src/Editor/Actions/ToggleGameStopAction \
    $$PWD/src/Editor/Actions/ToggleGameUpdateAction \
    $$PWD/src/Editor/Actions/ToggleGlslEditorViewAction \
    $$PWD/src/Editor/Actions/ToggleWindowAction \

INCLUDEPATH += $$PWD/src/Editor/GUI \
    $$PWD/src/Editor/GUI/MainMenuBar \
    $$PWD/src/Editor/GUI/StatusBar \

INCLUDEPATH += $$PWD/src/Editor/GUI/ContextMenus \
    $$PWD/src/Editor/GUI/ContextMenus/ContextMenu \
    $$PWD/src/Editor/GUI/ContextMenus/ShaderComboBoxContextMenu \

INCLUDEPATH += $$PWD/src/Editor/GUI/SubMenus \
    $$PWD/src/Editor/GUI/SubMenus/FileSubMenu \
    $$PWD/src/Editor/GUI/SubMenus/GameSubMenu \
    $$PWD/src/Editor/GUI/SubMenus/SubMenu \
    $$PWD/src/Editor/GUI/SubMenus/WindowSubMenu \

INCLUDEPATH += $$PWD/src/Editor/GUI/Widgets \
    $$PWD/src/Editor/GUI/Widgets/EWCollapsingHeader

INCLUDEPATH += $$PWD/src/Editor/GUI/Widgets/ApplicationOptionsWidgets \
    $$PWD/src/Editor/GUI/Widgets/ApplicationOptionsWidgets/EWEditorHotkeyTable \
    $$PWD/src/Editor/GUI/Widgets/ApplicationOptionsWidgets/EWFetchUserInput \
    $$PWD/src/Editor/GUI/Widgets/ApplicationOptionsWidgets/EWGameHotkeyTable \
    $$PWD/src/Editor/GUI/Widgets/ApplicationOptionsWidgets/EWHotkeyTable \
    $$PWD/src/Editor/GUI/Widgets/ApplicationOptionsWidgets/EWSelectApplicationOption \

INCLUDEPATH += $$PWD/src/Editor/GUI/Widgets/EWOpenGLViewport \
    $$PWD/src/Editor/GUI/Widgets/EWOpenGLViewport/EWOpenGLViewportDropZone \
    $$PWD/src/Editor/GUI/Widgets/EWOpenGLViewport/EWOpenGLViewportInput \
    $$PWD/src/Editor/GUI/Widgets/EWOpenGLViewport/EWOpenGLViewportTime \

INCLUDEPATH += $$PWD/src/Editor/GUI/Widgets/FileExplorerWidgets \
    $$PWD/src/Editor/GUI/Widgets/FileExplorerWidgets/EWDirectoryButton \
    $$PWD/src/Editor/GUI/Widgets/FileExplorerWidgets/EWDirectoryHistoryBar \
    $$PWD/src/Editor/GUI/Widgets/FileExplorerWidgets/EWFileExplorer \
    $$PWD/src/Editor/GUI/Widgets/FileExplorerWidgets/EWFileExplorerIconProvider \
    $$PWD/src/Editor/GUI/Widgets/FileExplorerWidgets/EWFileExplorerListView \
    $$PWD/src/Editor/GUI/Widgets/FileExplorerWidgets/EWFileExplorerTreeView \
    $$PWD/src/Editor/GUI/Widgets/FileExplorerWidgets/EWFileExplorerView \

INCLUDEPATH += $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslEditor \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslEditorEditMenu \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslEditorFileMenu \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslEditorMenuBar \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslEditorViewMenu \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslPlainTextEdit \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslSrcEditor \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslSyntaxHighlighter \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslTextEditLineNumArea \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWShaderComboBox \

INCLUDEPATH += $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/SyntaxHighlightBehaviour \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/SyntaxHighlightBehaviour/GlslCollectionHighlight \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/SyntaxHighlightBehaviour/GlslExpressionHighlight \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/SyntaxHighlightBehaviour/SyntaxHighlightBehaviour \

INCLUDEPATH += $$PWD/src/Editor/GUI/Widgets/MessageLogWidgets \
    $$PWD/src/Editor/GUI/Widgets/MessageLogWidgets/EWMessageLog \

INCLUDEPATH += $$PWD/src/Editor/GUI/Windows \
    $$PWD/src/Editor/GUI/Windows/EApplicationOptionsWindow \
    $$PWD/src/Editor/GUI/Windows/EFileExplorerWindow \
    $$PWD/src/Editor/GUI/Windows/EGlslEditorWindow \
    $$PWD/src/Editor/GUI/Windows/EMessageLogWindow \
    $$PWD/src/Editor/GUI/Windows/EWindow \
    $$PWD/src/Editor/GUI/Windows/EWindowManager \

INCLUDEPATH += $$PWD/src/Editor/Input \
    $$PWD/src/Editor/Input/BaseInput \
    $$PWD/src/Editor/Input/EInput \
    $$PWD/src/Editor/Input/InputCapture \
    $$PWD/src/Editor/Input/InputKey \
    $$PWD/src/Editor/Input/InputContainer \

INCLUDEPATH += $$PWD/src/Editor/Renderer \
    $$PWD/src/Editor/Renderer/ERenderEngine \

INCLUDEPATH += $$PWD/src/Editor/Startup \
    $$PWD/src/Editor/Startup/EActionStartup \

INCLUDEPATH += $$PWD/src/Editor/Startup/Cameras \
    $$PWD/src/Editor/Startup/Cameras/ECamera \

INCLUDEPATH += $$PWD/src/Editor/Startup/Materials \
    $$PWD/src/Editor/Startup/Materials/EDefaultMaterial \

INCLUDEPATH += $$PWD/src/Editor/Startup/Meshes \
    $$PWD/src/Editor/Startup/Meshes/EGridMesh \

INCLUDEPATH += $$PWD/src/Editor/Startup/Renderables \
    $$PWD/src/Editor/Startup/Renderables/EGridRenderable \

INCLUDEPATH += $$PWD/src/Editor/Startup/Shaders \
    $$PWD/src/Editor/Startup/Shaders/EGridShader \

INCLUDEPATH += $$PWD/src/Events \
    $$PWD/src/Events/AppStartEvent \
    $$PWD/src/Events/ECSOnUpdateEvent \

INCLUDEPATH += $$PWD/src/Game \
    $$PWD/src/Game/IEScene \

INCLUDEPATH += $$PWD/src/Game/ECS \
    $$PWD/src/Game/ECS/IEECS \
    $$PWD/src/Game/ECS/IEEntity \
    $$PWD/src/Game/ECS/IEEntityManager \

INCLUDEPATH += $$PWD/src/Game/ECS/Systems \
    $$PWD/src/Game/ECS/Systems/IEECSCameraSystem \
    $$PWD/src/Game/ECS/Systems/IEECSHierarchySystem \
    $$PWD/src/Game/ECS/Systems/IEECSInputSystem \
    $$PWD/src/Game/ECS/Systems/IEECSMaterialSystem \
    $$PWD/src/Game/ECS/Systems/IEECSMeshSystem \
    $$PWD/src/Game/ECS/Systems/IEECSNameSystem \
    $$PWD/src/Game/ECS/Systems/IEECSRigidbody3DSystem \
    $$PWD/src/Game/ECS/Systems/IEECSRenderableSystem \
    $$PWD/src/Game/ECS/Systems/IEECSScriptSystem \
    $$PWD/src/Game/ECS/Systems/IEECSShaderSystem \
    $$PWD/src/Game/ECS/Systems/IEECSSystem \
    $$PWD/src/Game/ECS/Systems/IEECSTransformSystem \

INCLUDEPATH += $$PWD/src/Game/GameState \
    $$PWD/src/Game/GameState/IEGamePlayState \
    $$PWD/src/Game/GameState/IEGameState \
    $$PWD/src/Game/GameState/IEGameStateType \
    $$PWD/src/Game/GameState/IEGameStopState \

INCLUDEPATH += $$PWD/src/Game/Graphics \
    $$PWD/src/Game/Graphics/IEBuffer \
    $$PWD/src/Game/Graphics/IEVertexBufferContainer \
    $$PWD/src/Game/Graphics/IEIndexBuffer \
    $$PWD/src/Game/Graphics/IEUniform \
    $$PWD/src/Game/Graphics/IEVertexBuffer \

INCLUDEPATH += $$PWD/src/Game/Managers \
    $$PWD/src/Game/Managers/IECameraManager \
    $$PWD/src/Game/Managers/IEMaterialManager \
    $$PWD/src/Game/Managers/IEMeshManager \
    $$PWD/src/Game/Managers/IERenderableManager \
    $$PWD/src/Game/Managers/IEResourceManager \
    $$PWD/src/Game/Managers/IEShaderManager \

INCLUDEPATH += $$PWD/src/Game/Physics \
    $$PWD/src/Game/Physics/IEBaseCollider \
    $$PWD/src/Game/Physics/IEBoxCollider \
    $$PWD/src/Game/Physics/IEBoxRigidBody \
    $$PWD/src/Game/Physics/IERigidBody \
    $$PWD/src/Game/Physics/IESimulationCallback \

INCLUDEPATH += $$PWD/src/Game/Resources \
    $$PWD/src/Game/Resources/IECamera \
    $$PWD/src/Game/Resources/IEMaterial \
    $$PWD/src/Game/Resources/IEMesh \
    $$PWD/src/Game/Resources/IERenderable \
    $$PWD/src/Game/Resources/IEResource \
    $$PWD/src/Game/Resources/IEShader \

INCLUDEPATH += $$PWD/src/Game/Scripting \

INCLUDEPATH += $$PWD/src/Game/Scripting/API \
    $$PWD/src/Game/Scripting/API/LuaApplication \
    $$PWD/src/Game/Scripting/API/LuaEnum \
    $$PWD/src/Game/Scripting/API/LuaIECamera \
    $$PWD/src/Game/Scripting/API/LuaUtility \
    $$PWD/src/Game/Scripting/API/LuaIEECS \
    $$PWD/src/Game/Scripting/API/LuaIEECSCameraSystem \
    $$PWD/src/Game/Scripting/API/LuaIEECSInputSystem \
    $$PWD/src/Game/Scripting/API/LuaIEECSScriptSystem \
    $$PWD/src/Game/Scripting/API/LuaIEECSTransformSystem \
    $$PWD/src/Game/Scripting/API/LuaIEEntity \
    $$PWD/src/Game/Scripting/API/LuaIEInput \
    $$PWD/src/Game/Scripting/API/LuaIEScript \
    $$PWD/src/Game/Scripting/API/LuaIETime \

INCLUDEPATH += $$PWD/src/Game/Scripting/API/LuaCommonType \
    $$PWD/src/Game/Scripting/API/LuaCommonType/LuaVec2Wrapper \
    $$PWD/src/Game/Scripting/API/LuaCommonType/LuaVec3Wrapper \
    $$PWD/src/Game/Scripting/API/LuaCommonType/LuaVec4Wrapper \
    $$PWD/src/Game/Scripting/API/LuaCommonType/LuaMat4Wrapper \

INCLUDEPATH += $$PWD/src/Game/Scripting/Scripts \
    $$PWD/src/Game/Scripting/Scripts/IECameraScript \
    $$PWD/src/Game/Scripting/Scripts/IEEntityScript \
    $$PWD/src/Game/Scripting/Scripts/IEScript \
    $$PWD/src/Game/Scripting/Scripts/ScriptData \

INCLUDEPATH += $$PWD/src/Game/Systems \
    $$PWD/src/Game/Systems/IEInput \
    $$PWD/src/Game/Systems/IERenderEngine \
    $$PWD/src/Game/Systems/IEScriptEngine \
    $$PWD/src/Game/Systems/IEPhysicsEngine \

INCLUDEPATH += $$PWD/src/Game/Systems/IETime \
    $$PWD/src/Game/Systems/IETime/DeltaTime

INCLUDEPATH += $$PWD/src/Serialize \
    $$PWD/src/Serialize/Serializable \

INCLUDEPATH += $$PWD/src/Utility \
    $$PWD/src/Utility/IEFile \
    $$PWD/src/Utility/IEGlslImporter \
    $$PWD/src/Utility/IEHash \
    $$PWD/src/Utility/IEObjExporter \
    $$PWD/src/Utility/IEObjImporter \
    $$PWD/src/Utility/IERandomNumber \
    $$PWD/src/Utility/IESerialize \
    $$PWD/src/Utility/IEStyleSheet \

INCLUDEPATH += $$PWD/tests \
    $$PWD/tests/IETCreateRenderable \
#    $$PWD/tests/IETBasicPhysics
