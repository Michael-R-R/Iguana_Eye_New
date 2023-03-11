#include "SaveGameFileAction.h"
#include <QFileDialog>
#include "ApplicationWindow.h"

SaveGameFileAction::SaveGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent) :
    MenuAction("Save File", shortcut, parent)
{
    connect(this, &SaveGameFileAction::triggered, window, [this, window]()
    {
        QString path = window->getSavePath();
        if(path.isEmpty())
        {
            path = askForPath(window);
            if(path.isEmpty())
                return;

            trySavePath(path, window);
        }
        else
        {
            trySavePath(path, window);
        }
    });
}

SaveGameFileAction::~SaveGameFileAction()
{

}

QString SaveGameFileAction::askForPath(QWidget* parent)
{
    return QFileDialog::getSaveFileName(parent, "Save File", ".", "Iguana Eye File (*.iedat)");
}

void SaveGameFileAction::trySavePath(const QString path, ApplicationWindow* window)
{
    if(!window->saveToFile(path))
        return;

    window->setSavePath(path);
    window->modifyTitle(path);
    window->setModified(false);
}
