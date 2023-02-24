#include "Editor.h"
#include "AppStartEvent.h"
#include "EActionStartup.h"
#include "ESceneStartup.h"

Editor::Editor(QObject* parent) :
    QObject(parent),
    input(nullptr),
    ui(nullptr),
    glViewportDropZone(nullptr)
{

}

Editor::~Editor()
{

}

void Editor::init()
{
    input = new EInput(this);
    ui = new EGUI(this);
    glViewportDropZone = new EWOpenGLViewportDropZone();
}

void Editor::startup(const AppStartEvent& event)
{
    // *** DO NOT REORDER *** //
    input->startup();
    ui->startup(event);
    glViewportDropZone->startup(event);

    EActionStartup::startup(event);
    ESceneStartup::startup(event);
}

void Editor::shutdown()
{
    delete glViewportDropZone;
    delete ui;
    delete input;
}
