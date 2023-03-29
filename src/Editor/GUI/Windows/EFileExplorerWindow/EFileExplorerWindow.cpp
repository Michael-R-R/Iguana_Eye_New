#include "EFileExplorerWindow.h"

EFileExplorerWindow::EFileExplorerWindow(QWidget* parent) :
    EWindow("File Explorer", parent),
    fileExplWidget(new EWFileExplorer(this))
{
    this->setWidget(fileExplWidget);
}

void EFileExplorerWindow::startup(const AppStartEvent&)
{
    fileExplWidget->startup();
}
