#include "ToggleEditorUiAction.h"
#include "EGUI.h"

ToggleEditorUiAction::ToggleEditorUiAction(InputKey* shortcut, EGUI* ui, QObject* parent) :
    MenuAction("Toggle Ui", shortcut, parent),
    status(true)
{
    connect(this, &QAction::triggered, this, [this, ui]()
    {
        status = !status;

        ui->showUi(status);
    });
}

ToggleEditorUiAction::~ToggleEditorUiAction()
{

}
