#include "EWFileExplorerTreeView.h"

EWFileExplorerTreeView::EWFileExplorerTreeView(QFileSystemModel* model, QWidget* parent) :
    QTreeView(parent),
    EWFileExplorerView(model)
{
    this->setFocusPolicy(Qt::NoFocus);
    this->setDragEnabled(false);
    this->setExpandsOnDoubleClick(false);
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setUniformRowHeights(true);
    this->setModel(fileModel);
    this->setHeaderHidden(true);
    for(int i = 1; i < fileModel->columnCount(); i++)
    {
        this->hideColumn(i);
    }

    connect(this, &EWFileExplorerTreeView::doubleClicked, this, &EWFileExplorerTreeView::onDoubleClicked);
}

void EWFileExplorerTreeView::startup(const QModelIndex rootIndex)
{
    this->setRootIndex(rootIndex);
}

QString EWFileExplorerTreeView::getCurrentDirectory()
{
    return fileModel->filePath(this->currentIndex());
}

void EWFileExplorerTreeView::onDoubleClicked(QModelIndex index)
{
    QFileInfo info(fileModel->filePath(index));
    if(!info.isDir())
        return;

    this->expand(index);
    this->clearSelection();

    emit folderDoubleClicked(info.filePath());
}
