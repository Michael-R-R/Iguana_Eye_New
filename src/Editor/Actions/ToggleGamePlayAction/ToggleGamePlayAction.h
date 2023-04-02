#pragma once

#include "BaseAction.h"

class IEGame;

class ToggleGamePlayAction : public BaseAction
{

public:
    ToggleGamePlayAction(IEGame& game, InputKey& shortcut, QObject* parent = nullptr);
    ~ToggleGamePlayAction();
};

