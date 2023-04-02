#pragma once

#include "BaseAction.h"

class IETime;

class ToggleGameRenderAction : public BaseAction
{

public:
    ToggleGameRenderAction(InputKey& shortcut, IETime& time, QObject* parent = nullptr);
    ~ToggleGameRenderAction();
};

