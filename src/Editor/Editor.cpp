#include "Editor.h"
#include "AppStartEvent.h"
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>

Editor::Editor(QObject* parent) :
    QObject(parent),
    glExtraFunc(nullptr),
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
    glExtraFunc = QOpenGLContext::currentContext()->extraFunctions();

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

void Editor::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
