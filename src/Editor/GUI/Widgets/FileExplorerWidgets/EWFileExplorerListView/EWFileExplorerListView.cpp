#include "EWFileExplorerListView.h"
#include "OpenGLFileHandler.h"

EWFileExplorerListView::EWFileExplorerListView(QFileSystemModel* model, QWidget* parent) :
    QListView(parent),
    EWFileExplorerView(model)
{
    this->setFocusPolicy(Qt::NoFocus);
    this->setViewMode(QListView::IconMode);
    this->setResizeMode(QListView::Adjust);
    this->setMovement(QListView::Static);
    this->setDragEnabled(true);
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setIconSize(QSize(36, 36));
    this->setUniformItemSizes(true);
    this->setModel(fileModel);

    connect(this, &EWFileExplorerListView::doubleClicked, this, &EWFileExplorerListView::onDoubleClicked);
}

void EWFileExplorerListView::startup(const QModelIndex rootIndex)
{
    this->setRootIndex(rootIndex);
}

QString EWFileExplorerListView::getCurrentDirectory()
{
    return fileModel->filePath(this->currentIndex());
}

void EWFileExplorerListView::onDoubleClicked(QModelIndex index)
{
    QFileInfo info(fileModel->filePath(index));
    if(info.isDir())
    {
        this->setRootIndex(index);

        emit folderDoubleClicked(info.filePath());

        this->clearSelection();
    }
    else
    {
        OpenGLFileHandler fileHandler;
        fileHandler.handle(info.absoluteFilePath());
    }
}
