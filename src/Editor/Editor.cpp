#include "Editor.h"
#include "AppStartEvent.h"
#include "EActionStartup.h"
#include "ESceneStartup.h"

Editor::Editor(QObject* parent) :
    QObject(parent),
    input(new EInput(this)),
    ui(new EGUI(this)),
    gameFileDropZone(new EWOpenGLViewportDropZone())
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
    delete gameFileDropZone;
    delete ui;
    delete input;
}
