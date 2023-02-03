#include "SaveAsGameAction.h"
#include <QFileDialog>
#include "ApplicationWindow.h"

SaveAsGameAction::SaveAsGameAction(ApplicationWindow* window, InputKey* shortcut, QObject* parent) :
    MenuAction("Save As", shortcut, parent)
{
    connect(this, &SaveAsGameAction::triggered, window, [this, window]()
    {
        QString path = askForPath(window);
        if(path.isEmpty())
            return;

        trySavePath(path, window);
    });
}

SaveAsGameAction::~SaveAsGameAction()
{

}

QString SaveAsGameAction::askForPath(QWidget* parent)
{
    return QFileDialog::getSaveFileName(parent, "Save As File", ".", "Iguana Eye File (*.iedat)");
}

void SaveAsGameAction::trySavePath(const QString path, ApplicationWindow* window)
{
    if(!window->saveToFile(path))
        return;

    window->setSavePath(path);
    window->addTextToTitle(path);
    window->displayModifiedStatus(false);
}
