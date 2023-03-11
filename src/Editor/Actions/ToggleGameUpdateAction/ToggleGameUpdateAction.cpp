#include "ToggleGameUpdateAction.h"
#include "IETime.h"

ToggleGameUpdateAction::ToggleGameUpdateAction(InputKey* shortcut, IETime& time, QObject* parent) :
    MenuAction("Update", shortcut, parent)
{
    this->setCheckable(true);
    this->setChecked(true);

    connect(this, &QAction::triggered, &time, [this, &time](bool val)
    {
        if(!val)
            time.stopUpdateTimer();
        else
            time.startUpdateTimer();
    });
}

ToggleGameUpdateAction::~ToggleGameUpdateAction()
{

}
