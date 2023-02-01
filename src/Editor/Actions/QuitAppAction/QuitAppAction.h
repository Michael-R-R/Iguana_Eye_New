#pragma once

#include <QAction>

#include "MenuAction.h"

class QuitAppAction : public MenuAction
{

public:
    QuitAppAction(InputKey* shortcut, QObject* parent = nullptr);
    ~QuitAppAction();
};

