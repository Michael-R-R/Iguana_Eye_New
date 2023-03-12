#include "Editor.h"
#include "AppStartEvent.h"
#include "EActionStartup.h"
#include "ESceneStartup.h"

Editor::Editor(QObject* parent) :
    QObject(parent),
    input(std::make_unique<EInput>()),
    ui(std::make_unique<EGUI>(this)),
    gameFileDropZone(std::make_unique<EWOpenGLViewportDropZone>())
{

}

Editor::~Editor()
{

}

void Editor::startup(const AppStartEvent& event)
{
    // *** DO NOT REORDER *** //
    input->startup();
    ui->startup(event);
    gameFileDropZone->startup(event);

    EActionStartup::startup(event);
    ESceneStartup::startup(event);
}

void Editor::shutdown()
{

}
