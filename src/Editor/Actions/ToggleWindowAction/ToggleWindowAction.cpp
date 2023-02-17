#include "ToggleWindowAction.h"
#include "EWindow.h"

ToggleWindowAction::ToggleWindowAction(const QString& title,
                                       InputKey* shortcut,
                                       EWindow* window,
                                       QObject *parent) :
    MenuAction(title, shortcut, parent)
{
    connect(this, &QAction::triggered, this, [this, window]()
    {
        if(!window) { return; }

        if(window->isHidden()) { window->show(); }
        else { window->close(); }
    });
}

ToggleWindowAction::~ToggleWindowAction()
{

}
