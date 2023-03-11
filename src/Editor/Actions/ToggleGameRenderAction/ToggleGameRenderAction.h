#pragma once

#include "MenuAction.h"

class IETime;

class ToggleGameRenderAction : public MenuAction
{

public:
    ToggleGameRenderAction(InputKey& shortcut, IETime& time, QObject* parent = nullptr);
    ~ToggleGameRenderAction();
};

