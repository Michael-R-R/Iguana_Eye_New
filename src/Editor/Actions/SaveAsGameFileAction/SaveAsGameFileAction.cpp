#include "SaveAsGameFileAction.h"
#include <QFileDialog>
#include "ApplicationWindow.h"

SaveAsGameFileAction::SaveAsGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent) :
    BaseAction("Save File As", shortcut, parent)
{
    connect(this, &SaveAsGameFileAction::triggered, window, [this, window]()
            {
                QString path = QFileDialog::getSaveFileName(window,
                                                            "Save As File",
                                                            ".",
                                                            "Iguana Eye File (*.iedat)");
                if(path.isEmpty())
                    return;

                window->saveAsToFile(path);
            });
}

SaveAsGameFileAction::~SaveAsGameFileAction()
{

}
