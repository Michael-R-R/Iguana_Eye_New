#include "EFileExplorerWindow.h"

EFileExplorerWindow::EFileExplorerWindow(QWidget* parent) :
    EWindow("File Explorer", parent),
    fileExplWidget(new EWFileExplorer(this))
{
    this->setWidget(fileExplWidget);
}

EFileExplorerWindow::~EFileExplorerWindow()
{

}

void EFileExplorerWindow::startup()
{
    fileExplWidget->startup();
}
