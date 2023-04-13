#include "Editor.h"
#include "EInput.h"
#include "EGUI.h"
#include "EWOpenGLViewportDropZone.h"
#include "EActionStartup.h"

Editor::Editor(QWidget* parent) :
    QWidget(parent),
    input(new EInput(this)),
    ui(new EGUI(this)),
    viewportDropZone(new EWOpenGLViewportDropZone())
{

}

Editor::~Editor()
{

}

void Editor::startup()
{
    // *** DO NOT REORDER *** //
    input->startup();
    ui->startup();
    viewportDropZone->startup();

    EActionStartup::startup();
}

void Editor::shutdown()
{
    viewportDropZone->shutdown();
    ui->shutdown();
    input->shutdown();
}
