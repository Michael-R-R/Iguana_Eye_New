#include "Editor.h"
#include "AppStartEvent.h"
#include "EInput.h"
#include "EGUI.h"
#include "EWOpenGLViewportDropZone.h"
#include "EActionStartup.h"

Editor Editor::mInstance;
Editor& Editor::instance() { return mInstance; }

Editor::Editor() :
    QObject(),
    input(nullptr),
    ui(nullptr),
    viewportDropZone(nullptr)
{

}

Editor::~Editor()
{

}

void Editor::startup(const AppStartEvent& event)
{
    input = new EInput(this);
    ui = new EGUI(this);
    viewportDropZone = new EWOpenGLViewportDropZone();

    // *** DO NOT REORDER *** //
    ui->startup(event);
    viewportDropZone->startup(event);

    EActionStartup::startup(event);
}

void Editor::shutdown()
{
    delete viewportDropZone;
    delete ui;
    delete input;
}
