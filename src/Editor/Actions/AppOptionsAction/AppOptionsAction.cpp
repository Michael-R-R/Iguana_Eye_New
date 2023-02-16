#include "AppOptionsAction.h"
#include "EWindowManager.h"

AppOptionsAction::AppOptionsAction(InputKey* shortcut,
                                   EWindowManager* windowManager,
                                   QObject *parent) :
    MenuAction("Options", shortcut, parent)
{
    connect(this, &QAction::triggered, this, [this, windowManager]()
    {
        auto window = windowManager->getValue("Options");
        if(!window) { return; }

        if(window->isHidden()) { window->show(); }
        else { window->close(); }
    });
}

AppOptionsAction::~AppOptionsAction()
{

}
