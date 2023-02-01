#include "AppOptionsWindow.h"
#include "AppStartEvent.h"
#include "SelectAppOptionsWidget.h"

AppOptionsWindow::AppOptionsWindow(QWidget* parent) :
    Window("Options", parent),
    selectOptionsWidget(new SelectAppOptionsWidget(this))
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);
    this->setFloating(true);
    this->setWidget(selectOptionsWidget);
}

AppOptionsWindow::~AppOptionsWindow()
{

}

void AppOptionsWindow::setup(const AppStartEvent& event)
{
    auto editorInput = event.editor()->getInput();
    auto editorInputContainer = editorInput->getInputContainer();

    auto gameInput = event.game()->getInput();
    auto gameInputContainer = gameInput->getInputContainer();

    selectOptionsWidget->setupGameGroupBox(gameInputContainer);
    selectOptionsWidget->setupEditorGroupBox(editorInputContainer);
}
