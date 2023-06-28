#include "OpenGameFileAction.h"
#include "ApplicationWindow.h"
#include <QFileDialog>
#include <QMessageBox>

OpenGameFileAction::OpenGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent) :
    BaseAction("Open File", shortcut, parent)
{
    connect(this, &OpenGameFileAction::triggered, window, [this, window]()
            {
                QString path = QFileDialog::getOpenFileName(window,
                                                            "Open File",
                                                            ".",
                                                            "Iguana Eye File (*.iedat)");
                if(path.isEmpty())
                    return;

                window->openFile(path);
            });
}

OpenGameFileAction::~OpenGameFileAction()
{

}
