#include "ToggleGameRenderAction.h"
#include "IETime.h"

ToggleGameRenderAction::ToggleGameRenderAction(InputKey& shortcut, IETime& time, QObject* parent) :
    MenuAction("Render", shortcut, parent)
{
    this->setCheckable(true);
    this->setChecked(true);

    connect(this, &QAction::triggered, &time, [this, &time](bool val)
    {
        if(!val)
            time.stopRenderTimer();
        else
            time.startRenderTimer();
    });
}

ToggleGameRenderAction::~ToggleGameRenderAction()
{

}
