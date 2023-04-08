#include "NewGameFileAction.h"
#include "ApplicationWindow.h"
#include <QMessageBox>

NewGameFileAction::NewGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent) :
    BaseAction("New File", shortcut, parent)
{
    connect(this, &BaseAction::triggered, this, [window]()
    {
        window->newFile();
    });
}
