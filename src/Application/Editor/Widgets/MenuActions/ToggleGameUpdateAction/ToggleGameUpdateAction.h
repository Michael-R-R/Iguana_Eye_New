#pragma once

#include "MenuAction.h"

class IETime;

class ToggleGameUpdateAction : public MenuAction
{

public:
    ToggleGameUpdateAction(InputKey* shortcut, IETime* time, QObject* parent = nullptr);
    ~ToggleGameUpdateAction();
};

