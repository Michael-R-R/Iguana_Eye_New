#pragma once

#include "BaseAction.h"

class IEGame;

class ToggleGameStopAction : public BaseAction
{

public:
    ToggleGameStopAction(IEGame* game, InputKey& shortcut, QObject* parent = nullptr);
    ~ToggleGameStopAction();
};

