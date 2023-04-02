#include "NewGameFileAction.h"
#include "ApplicationWindow.h"
#include <QMessageBox>

NewGameFileAction::NewGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent) :
    BaseAction("New File", shortcut, parent)
{
    connect(this, &BaseAction::triggered, this, [window]()
    {
        // Ask to save file before opening a new file
        QString savePath = window->getSavePath();
        if(!savePath.isEmpty())
        {
            int answer = QMessageBox::question(window, "Save File?", "Save before closing?",
                                               QMessageBox::No | QMessageBox::Yes);
            if(answer == QMessageBox::Yes)
                window->saveToFile(savePath);
        }

        window->newFile();
        window->setSavePath("");
        window->modifyTitle("");
    });
}
