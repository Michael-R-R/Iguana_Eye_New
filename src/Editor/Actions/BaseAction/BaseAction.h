#pragma once

#include <QAction>

#include "InputKey.h"

class BaseAction : public QAction
{

public:
    BaseAction(QString title, InputKey& shortcut, QObject* parent = nullptr);
    ~BaseAction();
};

