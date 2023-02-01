#include "ToggleUiAction.h"
#include "EditorUi.h"

ToggleUiAction::ToggleUiAction(InputKey* shortcut, EditorUi* ui, QObject* parent) :
    MenuAction("Toggle Ui", shortcut, parent),
    status(true)
{
    connect(this, &QAction::triggered, this, [this, ui]()
    {
        status = !status;

        ui->showUi(status);
    });
}

ToggleUiAction::~ToggleUiAction()
{

}
