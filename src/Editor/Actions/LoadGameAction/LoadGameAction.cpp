#include "LoadGameAction.h"
#include <QFileDialog>
#include "ApplicationWindow.h"

LoadGameAction::LoadGameAction(ApplicationWindow* window, InputKey* shortcut, QObject* parent) :
    MenuAction("Open", shortcut, parent)
{
    connect(this, &LoadGameAction::triggered, window, [this, window]()
    {
        QString path = askForPath(window);
        if(path.isEmpty())
            return;

        tryOpenPath(path, window);
    });
}

LoadGameAction::~LoadGameAction()
{

}

QString LoadGameAction::askForPath(QWidget* parent)
{
    return QFileDialog::getOpenFileName(parent, "Save File", ".", "Iguana Eye File (*.iedat)");
}

void LoadGameAction::tryOpenPath(const QString path, ApplicationWindow* window)
{
    if(!window->loadFromFile(path))
        return;

    window->setSavePath(path);
    window->addTextToTitle(path);
    window->displayApplicationModified(false);
}
