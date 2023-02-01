#include "Editor.h"
#include "AppStartEvent.h"

Editor::Editor(QObject* parent) :
    QObject(parent),
    input(new EditorInput(this)),
    ui(new EditorUi(this)),
    actions(new EditorActionManager(this))
{

}

Editor::~Editor()
{

}

void Editor::startup(const AppStartEvent& event)
{
    // *** Order matters *** //
    input->setup();
    ui->setup(event);
    actions->setup(event);
}

void Editor::shutdown()
{

}
