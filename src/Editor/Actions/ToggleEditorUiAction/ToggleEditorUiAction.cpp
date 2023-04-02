#include "ToggleEditorUiAction.h"
#include "EGUI.h"

ToggleEditorUiAction::ToggleEditorUiAction(InputKey& shortcut, EGUI* ui, QObject* parent) :
    BaseAction("Toggle Ui", shortcut, parent),
    status(true)
{
    connect(this, &QAction::triggered, this, [this, ui]()
    {
        status = !status;

        ui->toggleUi(status);
    });
}

ToggleEditorUiAction::~ToggleEditorUiAction()
{

}
