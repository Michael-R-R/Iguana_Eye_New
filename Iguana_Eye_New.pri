INCLUDEPATH += $$PWD/required/include \
INCLUDEPATH += $$PWD/required/include/lua \
INCLUDEPATH += $$PWD/required/include/physx \

INCLUDEPATH += $$PWD/src/Application \
    $$PWD/src/Application/ApplicationFileHandler \
    $$PWD/src/Application/ApplicationProperties \
    $$PWD/src/Application/ApplicationWindow \

INCLUDEPATH += $$PWD/src/Common \
    $$PWD/src/Common/IEEnum \
    $$PWD/src/Common/IEObject \

INCLUDEPATH += $$PWD/src/Common/Factory \
    $$PWD/src/Common/Factory/IEBufferObjectFactory \
    $$PWD/src/Common/Factory/IERenderableFactory \

INCLUDEPATH += $$PWD/src/Editor \

INCLUDEPATH += $$PWD/src/Editor/Actions \
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
    $$PWD/src/Editor/GUI/Widgets/EWOpenGLViewport/OpenGLFileHandler \

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
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslEditorFileMenu \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslEditorMenuBar \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslEditorViewMenu \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslPlainTextEdit \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslSrcEditor \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslSyntaxHighlighter \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWGlslTextEditLineNumArea \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/EWShaderComboBox \
    $$PWD/src/Editor/GUI/Widgets/GlslEditorWidgets/GlslFileHandler \

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

INCLUDEPATH += $$PWD/src/Editor/Startup/Meshes \
    $$PWD/src/Editor/Startup/Meshes/EGridMesh \

INCLUDEPATH += $$PWD/src/Editor/Startup/Renderables \
    $$PWD/src/Editor/Startup/Renderables/EGridRenderable \

INCLUDEPATH += $$PWD/src/Editor/Startup/Shaders \
    $$PWD/src/Editor/Startup/Shaders/EGridShader \

INCLUDEPATH += $$PWD/src/Game/ \

INCLUDEPATH += $$PWD/src/Game/GameState \
    $$PWD/src/Game/GameState/IEGamePlayState \
    $$PWD/src/Game/GameState/IEGameState \
    $$PWD/src/Game/GameState/IEGameStateType \
    $$PWD/src/Game/GameState/IEGameStopState \

INCLUDEPATH += $$PWD/src/Game/Resources \
    $$PWD/src/Game/Resources/IEResource \

INCLUDEPATH += $$PWD/src/Game/Resources/FileResource \
    $$PWD/src/Game/Resources/FileResource/IEFileResource \
    $$PWD/src/Game/Resources/FileResource/IEMaterial \
    $$PWD/src/Game/Resources/FileResource/IEMesh \
    $$PWD/src/Game/Resources/FileResource/IEScript \
    $$PWD/src/Game/Resources/FileResource/IEShader \
    $$PWD/src/Game/Resources/FileResource/IETexture2D \

INCLUDEPATH += $$PWD/src/Game/Resources/FileResource/IERenderable \
$$PWD/src/Game/Resources/FileResource/IERenderable/IEIndexRenderable \
$$PWD/src/Game/Resources/FileResource/IERenderable/IEInstIndexRenderable \
    $$PWD/src/Game/Resources/FileResource/IERenderable/IEInstRenderable \
    $$PWD/src/Game/Resources/FileResource/IERenderable/IEInstVertRenderable \
    $$PWD/src/Game/Resources/FileResource/IERenderable/IEVertRenderable \

INCLUDEPATH += $$PWD/src/Game/Resources/SceneResource \
    $$PWD/src/Game/Resources/SceneResource/IECamera \
    $$PWD/src/Game/Resources/SceneResource/IESceneResource \

INCLUDEPATH += $$PWD/src/Game/System \
    $$PWD/src/Game/System/IEInput \
    $$PWD/src/Game/System/IERenderEngine \
    $$PWD/src/Game/System/IEScene \
    $$PWD/src/Game/System/IEUboManager \

INCLUDEPATH += $$PWD/src/Game/System/IEECS \
    $$PWD/src/Game/System/IEECS/IEEntity \
    $$PWD/src/Game/System/IEECS/IEEntityManager \

INCLUDEPATH += $$PWD/src/Game/System/IEECS/IEECSSystem \
    $$PWD/src/Game/System/IEECS/IEECSSystem/IEECSCameraSystem \
    $$PWD/src/Game/System/IEECS/IEECSSystem/IEECSColliderSystem \
    $$PWD/src/Game/System/IEECS/IEECSSystem/IEECSHierarchySystem \
    $$PWD/src/Game/System/IEECS/IEECSSystem/IEECSNameSystem \
    $$PWD/src/Game/System/IEECS/IEECSSystem/IEECSRigidbody3DSystem \
    $$PWD/src/Game/System/IEECS/IEECSSystem/IEECSScriptSystem \
    $$PWD/src/Game/System/IEECS/IEECSSystem/IEECSTransformSystem \

INCLUDEPATH += $$PWD/src/Game/System/IEECS/IEECSSystem/IEECSResourceSystem \
    $$PWD/src/Game/System/IEECS/IEECSSystem/IEECSResourceSystem/IEECSMaterialSystem \
    $$PWD/src/Game/System/IEECS/IEECSSystem/IEECSResourceSystem/IEECSMeshSystem \
    $$PWD/src/Game/System/IEECS/IEECSSystem/IEECSResourceSystem/IEECSRenderableSystem \
    $$PWD/src/Game/System/IEECS/IEECSSystem/IEECSResourceSystem/IEECSShaderSystem \

INCLUDEPATH += $$PWD/src/Game/System/IEPhysicsEngine \
    $$PWD/src/Game/System/IEPhysicsEngine/IESimulationCallback \

INCLUDEPATH += $$PWD/src/Game/System/IEPhysicsEngine/IECollider \
    $$PWD/src/Game/System/IEPhysicsEngine/IECollider/IEBaseCollider \
    $$PWD/src/Game/System/IEPhysicsEngine/IECollider/IEBoxCollider \
    $$PWD/src/Game/System/IEPhysicsEngine/IECollider/IECapsuleCollider \
    $$PWD/src/Game/System/IEPhysicsEngine/IECollider/IESphereCollider \

INCLUDEPATH += $$PWD/src/Game/System/IEPhysicsEngine/IERigidbody \
    $$PWD/src/Game/System/IEPhysicsEngine/IERigidbody/IEBoxRigidbody \
    $$PWD/src/Game/System/IEPhysicsEngine/IERigidbody/IECapsuleRigidbody \
    $$PWD/src/Game/System/IEPhysicsEngine/IERigidbody/IEPlaneRigidbody \
    $$PWD/src/Game/System/IEPhysicsEngine/IERigidbody/IEBaseRigidbody \
    $$PWD/src/Game/System/IEPhysicsEngine/IERigidbody/IESphereRigidbody \

INCLUDEPATH += $$PWD/src/Game/System/IEScriptEngine \
    $$PWD/src/Game/System/IEScriptEngine/IEScriptData \

INCLUDEPATH += $$PWD/src/Game/System/IEScriptEngine/API \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaApplication \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaEnum \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaIECamera \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaUtility \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaIEECS \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaIEECSCameraSystem \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaIEECSScriptSystem \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaIEECSTransformSystem \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaIEEntity \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaIEInput \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaIEScript \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaIETime \

INCLUDEPATH += $$PWD/src/Game/System/IEScriptEngine/API/LuaCommonType \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaCommonType/LuaVec2Wrapper \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaCommonType/LuaVec3Wrapper \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaCommonType/LuaVec4Wrapper \
    $$PWD/src/Game/System/IEScriptEngine/API/LuaCommonType/LuaMat4Wrapper \

INCLUDEPATH += $$PWD/src/Game/System/IETime \
    $$PWD/src/Game/System/IETime/DeltaTime

INCLUDEPATH += $$PWD/src/Game/System/IEManager \
    $$PWD/src/Game/System/IEManager/IECameraManager \
    $$PWD/src/Game/System/IEManager/IEMaterialManager \
    $$PWD/src/Game/System/IEManager/IEMeshManager \
    $$PWD/src/Game/System/IEManager/IERenderableManager \
    $$PWD/src/Game/System/IEManager/IEResourceManager \
    $$PWD/src/Game/System/IEManager/IEShaderManager \
    $$PWD/src/Game/System/IEManager/IETexture2DManager \

INCLUDEPATH += $$PWD/src/OpenGL \

INCLUDEPATH += $$PWD/src/OpenGL/Buffer \
    $$PWD/src/OpenGL/Buffer/IEBufferObject \
    $$PWD/src/OpenGL/Buffer/IEIndexBufferObject \
    $$PWD/src/OpenGL/Buffer/IEUniformBufferObject \
    $$PWD/src/OpenGL/Buffer/IEVertexBufferObject \

INCLUDEPATH += $$PWD/src/OpenGL/Include \
    $$PWD/src/OpenGL/Include/GLInclude \

INCLUDEPATH += $$PWD/src/OpenGL/Struct \

INCLUDEPATH += $$PWD/src/OpenGL/Uniform \
    $$PWD/src/OpenGL/Uniform/IEUniformData \

INCLUDEPATH += $$PWD/src/Test \
    $$PWD/src/Test/IETInstIndexRenderable \

INCLUDEPATH += $$PWD/src/Utility \
    $$PWD/src/Utility/IEFile \
    $$PWD/src/Utility/IEHash \
    $$PWD/src/Utility/IEMath \
    $$PWD/src/Utility/IERandomNumber \
    $$PWD/src/Utility/IEStyleSheet \

INCLUDEPATH += $$PWD/src/Utility/Export \
    $$PWD/src/Utility/Export/IEShaderExport \

INCLUDEPATH += $$PWD/src/Utility/IESerialize \
    $$PWD/src/Utility/IESerialize/IESerializeConverter \
    $$PWD/src/Utility/IESerialize/IESerializable \

INCLUDEPATH += $$PWD/src/Utility/Import \
    $$PWD/src/Utility/Import/IEMeshImport \
    $$PWD/src/Utility/Import/IEGlslImport \
