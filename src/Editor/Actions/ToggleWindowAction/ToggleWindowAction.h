#pragma once

#include <BaseAction.h>

class EWindow;

class ToggleWindowAction : public BaseAction
{

public:
    ToggleWindowAction(const QString& title,
                       InputKey& shortcut,
                       EWindow* window,
                       QObject* parent = nullptr);
    ~ToggleWindowAction();
};

