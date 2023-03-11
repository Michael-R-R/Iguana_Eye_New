#pragma once

#include <QAction>

#include "InputKey.h"

class MenuAction : public QAction
{

public:
    MenuAction(QString title, InputKey& shortcut, QObject* parent = nullptr);
    ~MenuAction();
};

