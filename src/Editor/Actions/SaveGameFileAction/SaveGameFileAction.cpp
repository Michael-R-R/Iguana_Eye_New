#include "SaveGameFileAction.h"
#include "ApplicationWindow.h"

SaveGameFileAction::SaveGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent) :
    BaseAction("Save File", shortcut, parent)
{
    connect(this, &SaveGameFileAction::triggered, window, [window]()
            {
                window->saveToFile();
            });
}

SaveGameFileAction::~SaveGameFileAction()
{

}
