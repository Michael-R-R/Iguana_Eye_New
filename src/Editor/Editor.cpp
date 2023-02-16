#include "Editor.h"
#include "AppStartEvent.h"
#include "EActionStartup.h"
#include "ESceneStartup.h"

Editor::Editor(QObject* parent) :
    QObject(parent),
    input(nullptr),
    ui(nullptr)
{

}

Editor::~Editor()
{

}

void Editor::init()
{
    input = new EInput(this);
    ui = new EGUI(this);
}

void Editor::startup(const AppStartEvent& event)
{
    // *** Order matters *** //
    input->startup();
    ui->startup(event);

    EActionStartup::startup(event);
    ESceneStartup::startup(event);
}

void Editor::shutdown()
{
    delete ui;
    delete input;
}
