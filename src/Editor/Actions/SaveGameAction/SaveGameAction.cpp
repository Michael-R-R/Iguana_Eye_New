#include "SaveGameAction.h"
#include <QFileDialog>
#include "ApplicationWindow.h"

SaveGameAction::SaveGameAction(ApplicationWindow* window, InputKey* shortcut, QObject* parent) :
    MenuAction("Save File", shortcut, parent)
{
    connect(this, &SaveGameAction::triggered, window, [this, window]()
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

SaveGameAction::~SaveGameAction()
{

}

QString SaveGameAction::askForPath(QWidget* parent)
{
    return QFileDialog::getSaveFileName(parent, "Save File", ".", "Iguana Eye File (*.iedat)");
}

void SaveGameAction::trySavePath(const QString path, ApplicationWindow* window)
{
    if(!window->saveToFile(path))
        return;

    window->setSavePath(path);
    window->addTextToTitle(path);
    window->modifiedStatus(false);
}
