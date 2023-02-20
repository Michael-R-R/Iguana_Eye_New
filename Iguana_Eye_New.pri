INCLUDEPATH += $$PWD/required/include

INCLUDEPATH += $$PWD/src/Application \
    $$PWD/src/Application/ApplicationWindow \

INCLUDEPATH += $$PWD/src/Editor \

INCLUDEPATH += $$PWD/src/Editor/Actions \
    $$PWD/src/Editor/Actions/CompileShaderAction \
    $$PWD/src/Editor/Actions/ToggleWindowAction \
    $$PWD/src/Editor/Actions/OpenGameFileAction \
    $$PWD/src/Editor/Actions/MenuAction \
    $$PWD/src/Editor/Actions/NewGameFileAction \
    $$PWD/src/Editor/Actions/NewShaderAction \
    $$PWD/src/Editor/Actions/QuitAppAction \
    $$PWD/src/Editor/Actions/SaveAsGameFileAction \
    $$PWD/src/Editor/Actions/SaveGameFileAction \
    $$PWD/src/Editor/Actions/ToggleGameRenderAction \
    $$PWD/src/Editor/Actions/ToggleGameUpdateAction \
    $$PWD/src/Editor/Actions/ToggleGlslEditorViewAction \
    $$PWD/src/Editor/Actions/ToggleEditorUiAction \

INCLUDEPATH += $$PWD/src/Editor/GUI \
    $$PWD/src/Editor/GUI/MainMenuBar \
    $$PWD/src/Editor/GUI/StatusBar \

INCLUDEPATH += $$PWD/src/Editor/Menus \
    $$PWD/src/Editor/Menus/FileSubMenu \
    $$PWD/src/Editor/Menus/GameSubMenu \

INCLUDEPATH += $$PWD/src/Editor/GUI/SubMenus \
    $$PWD/src/Editor/GUI/SubMenus/FileSubMenu \
    $$PWD/src/Editor/GUI/SubMenus/GameSubMenu \
    $$PWD/src/Editor/GUI/SubMenus/SubMenu \
    $$PWD/src/Editor/GUI/SubMenus/WindowSubMenu \

INCLUDEPATH += $$PWD/src/Editor/GUI/Widgets \

INCLUDEPATH += $$PWD/src/Editor/GUI/Widgets/ApplicationOptionsWidgets \
    $$PWD/src/Editor/GUI/Widgets/ApplicationOptionsWidgets/EWEditorHotkeyTable \
    $$PWD/src/Editor/GUI/Widgets/ApplicationOptionsWidgets/EWFetchUserInput \
    $$PWD/src/Editor/GUI/Widgets/ApplicationOptionsWidgets/EWGameHotkeyTable \
    $$PWD/src/Editor/GUI/Widgets/ApplicationOptionsWidgets/EWHotkeyTable \
    $$PWD/src/Editor/GUI/Widgets/ApplicationOptionsWidgets/EWSelectApplicationOption \

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

INCLUDEPATH += $$PWD/src/Editor/GUI/Widgets/EWCollapsingHeader \

INCLUDEPATH += $$PWD/src/Editor/GUI/Widgets/EWOpenGLViewport \
    $$PWD/src/Editor/GUI/Widgets/EWOpenGLViewport/EWOpenGLViewportInput \
    $$PWD/src/Editor/GUI/Widgets/EWOpenGLViewport/EWOpenGLViewportTime \

INCLUDEPATH += $$PWD/src/Editor/GUI/Windows \
    $$PWD/src/Editor/GUI/Windows/EApplicationOptionsWindow \
    $$PWD/src/Editor/GUI/Windows/EWindowManager \
    $$PWD/src/Editor/GUI/Windows/EGlslEditorWindow \
    $$PWD/src/Editor/GUI/Windows/EWindow \

INCLUDEPATH += $$PWD/src/Editor/Input \
    $$PWD/src/Editor/Input/EInput \
    $$PWD/src/Editor/Input/InputCapture \
    $$PWD/src/Editor/Input/InputKey \
    $$PWD/src/Editor/Input/InputContainer \

INCLUDEPATH += $$PWD/src/Editor/Startup \
    $$PWD/src/Editor/Startup/EActionStartup \
    $$PWD/src/Editor/Startup/ESceneStartup \

INCLUDEPATH += $$PWD/src/Editor/Startup/Materials \
    $$PWD/src/Editor/Startup/Materials/EDefaultMaterial

INCLUDEPATH += $$PWD/src/Editor/Startup/Meshes \
    $$PWD/src/Editor/Startup/Meshes/EGridMesh \

INCLUDEPATH += $$PWD/src/Events \
    $$PWD/src/Events/AppStartEvent \
    $$PWD/src/Events/ECSOnUpdateEvent \
    $$PWD/src/Events/GameStartEvent \
    $$PWD/src/Events/RenderEngineStartEvent \

INCLUDEPATH += $$PWD/src/Game \
    $$PWD/src/Game/IEObject \
    $$PWD/src/Game/IEScene \

INCLUDEPATH += $$PWD/src/Game/ECS \
    $$PWD/src/Game/ECS/IEComponentType \
    $$PWD/src/Game/ECS/IEECS \
    $$PWD/src/Game/ECS/IEEntity \
    $$PWD/src/Game/ECS/IEEntityManager \

INCLUDEPATH += $$PWD/src/Game/ECS/Systems \
    $$PWD/src/Game/ECS/Systems/IEECSHierarchySystem \
    $$PWD/src/Game/ECS/Systems/IEECSInputSystem \
    $$PWD/src/Game/ECS/Systems/IEECSMaterialSystem \
    $$PWD/src/Game/ECS/Systems/IEECSMeshSystem \
    $$PWD/src/Game/ECS/Systems/IEECSRenderableSystem \
    $$PWD/src/Game/ECS/Systems/IEECSShaderSystem \
    $$PWD/src/Game/ECS/Systems/IEECSSystem \
    $$PWD/src/Game/ECS/Systems/IEECSTransformSystem \

INCLUDEPATH += $$PWD/src/Game/IEGraphics \
    $$PWD/src/Game/IEGraphics/IEBuffer \
    $$PWD/src/Game/IEGraphics/IEVertexBufferContainer \
    $$PWD/src/Game/IEGraphics/IEIndexBuffer \
    $$PWD/src/Game/IEGraphics/IEUniform \
    $$PWD/src/Game/IEGraphics/IEVertexBuffer \

INCLUDEPATH += $$PWD/src/Game/IEResources \
    $$PWD/src/Game/IEResources/IEMaterial \
    $$PWD/src/Game/IEResources/IEMesh \
    $$PWD/src/Game/IEResources/IERenderable \
    $$PWD/src/Game/IEResources/IEResource \
    $$PWD/src/Game/IEResources/IEResourceContainer \
    $$PWD/src/Game/IEResources/IEShader \

INCLUDEPATH += $$PWD/src/Game/Managers \
    $$PWD/src/Game/Managers/IEManager \
    $$PWD/src/Game/Managers/IEMaterialManager \
    $$PWD/src/Game/Managers/IEMeshManager \
    $$PWD/src/Game/Managers/IENameManager \
    $$PWD/src/Game/Managers/IERenderableManager \
    $$PWD/src/Game/Managers/IEShaderManager \

INCLUDEPATH += $$PWD/src/Game/Systems \
    $$PWD/src/Game/Systems/IEInput \
    $$PWD/src/Game/Systems/IERenderEngine \

INCLUDEPATH += $$PWD/src/Game/Systems/IETime \
    $$PWD/src/Game/Systems/IETime/DeltaTime

INCLUDEPATH += $$PWD/src/Utility \
    $$PWD/src/Utility/IEFile \
    $$PWD/src/Utility/IEHash \
    $$PWD/src/Utility/IEObjExporter \
    $$PWD/src/Utility/IEObjLoader \
    $$PWD/src/Utility/IESerialize \
