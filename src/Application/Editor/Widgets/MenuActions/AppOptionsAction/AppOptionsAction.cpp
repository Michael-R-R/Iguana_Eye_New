#include "AppOptionsAction.h"
#include "EditorWindowManager.h"

AppOptionsAction::AppOptionsAction(InputKey* shortcut,
                                   EditorWindowManager* windowManager,
                                   QObject *parent) :
    MenuAction("Options", shortcut, parent)
{
    connect(this, &QAction::triggered, this, [this, windowManager]()
    {
        auto window = windowManager->getWindow("Options");
        if(!window) { return; }

        if(window->isHidden()) { window->show(); }
        else { window->close(); }
    });
}

AppOptionsAction::~AppOptionsAction()
{

}
