#include "Editor.h"
#include "AppStartEvent.h"
#include "EditorSceneStartup.h"

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
    input = new EditorInput(this);
    ui = new EditorUi(this);
    actions = new EditorActionManager(this);
}

void Editor::startup(const AppStartEvent& event)
{
    // *** Order matters *** //
    input->setup();
    ui->setup(event);
    actions->setup(event);

    EditorSceneStartup::startup(event);
}

void Editor::shutdown()
{
    delete actions;
    delete ui;
    delete input;
}
