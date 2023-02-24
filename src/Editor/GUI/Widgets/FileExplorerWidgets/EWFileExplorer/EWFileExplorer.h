#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QFileSystemModel>

#include "EWFileExplorerTreeView.h"
#include "EWFileExplorerListView.h"
#include "EWDirectoryHistoryBar.h"

class EWFileExplorer : public QWidget
{
    QVBoxLayout* vMainLayout;
    QSplitter* hSplitter;

    QFileInfo rootDir;
    QFileSystemModel* fileModel;
    EWFileExplorerTreeView* treeView;
    EWFileExplorerListView* listView;
    EWDirectoryHistoryBar* dirHistoryBar;

public:
    EWFileExplorer(QWidget* parent = nullptr);
    ~EWFileExplorer() {}

    void startup();

    EWFileExplorerTreeView* getTreeView() const { return treeView; }
    EWFileExplorerListView* getListView() const { return listView; }
    EWDirectoryHistoryBar* getDirHistoryBar() const  { return dirHistoryBar; }

private:
    void setup();

private slots:
    void setFileModelRootDirectory(const QString& path);
};

