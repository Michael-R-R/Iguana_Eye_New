#pragma once

#include "BaseAction.h"

class IETime;

class ToggleGameUpdateAction : public BaseAction
{

public:
    ToggleGameUpdateAction(InputKey& shortcut, IETime& time, QObject* parent = nullptr);
    ~ToggleGameUpdateAction();
};

