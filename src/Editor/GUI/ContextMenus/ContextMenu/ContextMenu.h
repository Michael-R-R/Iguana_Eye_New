#pragma once

#include <QMenu>

class ContextMenu : public QMenu
{

public:
    ContextMenu(QWidget* parent = nullptr);
    ~ContextMenu() {}
};

