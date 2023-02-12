#include "LoadGameAction.h"
#include "ApplicationWindow.h"
#include <QFileDialog>
#include <QMessageBox>

LoadGameAction::LoadGameAction(ApplicationWindow* window, InputKey* shortcut, QObject* parent) :
    MenuAction("Open File", shortcut, parent)
{
    connect(this, &LoadGameAction::triggered, window, [this, window]()
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
    return QFileDialog::getOpenFileName(parent, "Open File", ".", "Iguana Eye File (*.iedat)");
}

void LoadGameAction::tryOpenPath(const QString path, ApplicationWindow* window)
{
    if(!window->loadFromFile(path))
        return;

    window->setSavePath(path);
    window->addTextToTitle(path);
    window->modifiedStatus(false);
}
