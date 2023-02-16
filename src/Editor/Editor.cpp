#include "Editor.h"
#include "AppStartEvent.h"
#include "ESceneStartup.h"

Editor::Editor(QObject* parent) :
    QObject(parent),
    input(nullptr),
    ui(nullptr),
    actions(nullptr)
{

}

Editor::~Editor()
{

}

void Editor::init()
{
    input = new EInput(this);
    ui = new EGUI(this);
    actions = new EActionManager(this);
}

void Editor::startup(const AppStartEvent& event)
{
    // *** Order matters *** //
    input->setup();
    ui->setup(event);
    actions->setup(event);

    ESceneStartup::startup(event);
}

void Editor::shutdown()
{
    delete actions;
    delete ui;
    delete input;
}
