#pragma once

#include <QFileSystemModel>

class EWFileExplorerView
{
protected:
    // Does not own this pointer
    QFileSystemModel* fileModel;

public:
    EWFileExplorerView(QFileSystemModel* model);
    ~EWFileExplorerView();

    virtual void startup(const QModelIndex rootIndex) = 0;
    virtual QString getCurrentDirectory() = 0;

    QString getRootDirectory() { return fileModel->rootPath(); }

protected slots:
    virtual void onDoubleClicked(QModelIndex index) = 0;
};

