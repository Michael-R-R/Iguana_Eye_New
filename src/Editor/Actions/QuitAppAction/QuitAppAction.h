#pragma once

#include <QAction>

#include "BaseAction.h"

class QuitAppAction : public BaseAction
{

public:
    QuitAppAction(InputKey& shortcut, QObject* parent = nullptr);
    ~QuitAppAction();
};

