#include "AppOptionsWindow.h"
#include "SelectAppOptionsWidget.h"
#include "AppStartEvent.h"
#include "Editor.h"
#include "Game.h"

AppOptionsWindow::AppOptionsWindow(QWidget* parent) :
    Window("Options", parent),
    selectOptionsWidget(new SelectAppOptionsWidget(this))
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);
    this->resize(450, 250);
    this->setFloating(true);
    this->setWidget(selectOptionsWidget);
}

AppOptionsWindow::~AppOptionsWindow()
{

}

void AppOptionsWindow::setup(const AppStartEvent& event)
{
    auto editorInput = event.getEditor()->getInput();
    auto editorInputContainer = editorInput->getInputContainer();

    auto gameInput = event.getGame()->getIEInput();
    auto gameInputContainer = gameInput->getInputContainer();

    selectOptionsWidget->setupGameGroupBox(gameInputContainer);
    selectOptionsWidget->setupEditorGroupBox(editorInputContainer);
}
