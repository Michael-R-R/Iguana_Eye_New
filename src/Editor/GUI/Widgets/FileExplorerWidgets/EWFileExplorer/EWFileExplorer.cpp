#include "EWFileExplorer.h"
#include "IEFile.h"

EWFileExplorer::EWFileExplorer(QWidget* parent) :
    QWidget(parent),
    vMainLayout(new QVBoxLayout(this)),
    hSplitter(new QSplitter(this)),
    rootDir(IEFile::absolutePath("./resources/root")),
    fileModel(new QFileSystemModel(this)),
    fileIconProvider(),
    treeView(new EWFileExplorerTreeView(fileModel, this)),
    listView(new EWFileExplorerListView(fileModel, this)),
    dirHistoryBar(new EWDirectoryHistoryBar(IEFile::absolutePath("./resources/root/Content"), this))
{
    setup();
}

EWFileExplorer::~EWFileExplorer()
{

}

void EWFileExplorer::startup()
{
    fileModel->setIconProvider(&fileIconProvider);
    QModelIndex rootIndex = fileModel->setRootPath(rootDir.filePath());

    treeView->startup(rootIndex);
    listView->startup(rootIndex);
    dirHistoryBar->startup(treeView, listView);

    connect(treeView, &EWFileExplorerTreeView::folderDoubleClicked, this, &EWFileExplorer::setFileModelRootDirectory);
    connect(listView, &EWFileExplorerListView::folderDoubleClicked, this, &EWFileExplorer::setFileModelRootDirectory);
    connect(dirHistoryBar, &EWDirectoryHistoryBar::directoryUpdated, this, &EWFileExplorer::setFileModelRootDirectory);
}

void EWFileExplorer::setup()
{
    vMainLayout->addWidget(dirHistoryBar);
    vMainLayout->addWidget(hSplitter);
    hSplitter->addWidget(treeView);
    hSplitter->addWidget(listView);
}

void EWFileExplorer::setFileModelRootDirectory(const QString& path)
{
    QModelIndex index = fileModel->setRootPath(path);
    listView->setRootIndex(index);
}
