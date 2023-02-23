#include "EWFileExplorer.h"

EWFileExplorer::EWFileExplorer(QWidget* parent) :
    QWidget(parent),
    vMainLayout(new QVBoxLayout(this)),
    hSplitter(new QSplitter(this)),
    rootDir(QDir::currentPath() + "/resources/root"),
    fileModel(new QFileSystemModel(this)),
    treeView(new EWFileExplorerTreeView(fileModel, this)),
    dirHistoryBar(new EWDirectoryHistoryBar(rootDir.filePath() + "/Content", this))
{
    setup();
}

void EWFileExplorer::startup()
{
    QModelIndex rootIndex = fileModel->setRootPath(rootDir.filePath());
    treeView->startup(rootIndex);

    dirHistoryBar->startup(treeView);
}

void EWFileExplorer::setup()
{
    vMainLayout->addWidget(dirHistoryBar);
    vMainLayout->addWidget(hSplitter);
    hSplitter->addWidget(treeView);
}
