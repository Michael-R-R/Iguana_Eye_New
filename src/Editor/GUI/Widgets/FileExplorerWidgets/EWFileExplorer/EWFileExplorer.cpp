#include "EWFileExplorer.h"

EWFileExplorer::EWFileExplorer(QWidget* parent) :
    QWidget(parent),
    rootDirStr("./resources/root/Content"),
    vMainLayout(new QVBoxLayout(this)),
    hSplitter(new QSplitter(this)),
    dirHistoryBar(new EWDirectoryHistoryBar(rootDirStr, this))
{
    setup();
}

void EWFileExplorer::startup()
{
    dirHistoryBar->addDirectory(rootDirStr);
}

void EWFileExplorer::setup()
{
    vMainLayout->addWidget(dirHistoryBar);
    vMainLayout->addWidget(hSplitter);
}
