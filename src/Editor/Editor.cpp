#include "Editor.h"
#include "AppStartEvent.h"

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

void Editor::startup(const AppStartEvent& event)
{
    input = new EditorInput(this);
    ui = new EditorUi(this);
    actions = new EditorActionManager(this);

    // *** Order matters *** //
    input->setup();
    ui->setup(event);
    actions->setup(event);
}

void Editor::shutdown()
{
    delete actions;
    delete ui;
    delete input;
}
