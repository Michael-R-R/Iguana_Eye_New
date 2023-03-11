#include "SaveAsGameFileAction.h"
#include <QFileDialog>
#include "ApplicationWindow.h"

SaveAsGameFileAction::SaveAsGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent) :
    MenuAction("Save File As", shortcut, parent)
{
    connect(this, &SaveAsGameFileAction::triggered, window, [this, window]()
    {
        QString path = askForPath(window);
        if(path.isEmpty())
            return;

        trySavePath(path, window);
    });
}

SaveAsGameFileAction::~SaveAsGameFileAction()
{

}

QString SaveAsGameFileAction::askForPath(QWidget* parent)
{
    return QFileDialog::getSaveFileName(parent, "Save As File", ".", "Iguana Eye File (*.iedat)");
}

void SaveAsGameFileAction::trySavePath(const QString path, ApplicationWindow* window)
{
    if(!window->saveToFile(path))
        return;

    window->setSavePath(path);
    window->modifyTitle(path);
    window->setModified(false);
}
