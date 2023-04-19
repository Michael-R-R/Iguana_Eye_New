#include "EApplicationOptionsWindow.h"
#include "EWSelectApplicationOption.h"
#include "ApplicationWindow.h"
#include "Editor.h"
#include "IEGame.h"
#include "BaseInput.h"
#include "IEInput.h"
#include "EInput.h"

EApplicationOptionsWindow::EApplicationOptionsWindow(QWidget* parent) :
    EWindow("Options", parent),
    selectOptionsWidget(new EWSelectApplicationOption(this))
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);
    this->resize(450, 250);
    this->setFloating(true);
    this->setWidget(selectOptionsWidget);
}

EApplicationOptionsWindow::~EApplicationOptionsWindow()
{

}

void EApplicationOptionsWindow::startup()
{
    auto& application = ApplicationWindow::instance();
    auto* game = application.getGame();
    auto* editor = application.getEditor();

    BaseInput* gameInput = game->getInput();
    BaseInput* editorInput = editor->getInput();

    selectOptionsWidget->setupGameGroupBox(gameInput);
    selectOptionsWidget->setupEditorGroupBox(editorInput);
}
