#pragma once

#include "EWindow.h"

#include "EWFileExplorer.h"

class EFileExplorerWindow : public EWindow
{
    EWFileExplorer* fileExplWidget;

public:
    EFileExplorerWindow(QWidget* parent = nullptr);
    ~EFileExplorerWindow() {}

    void startup() override;
};

