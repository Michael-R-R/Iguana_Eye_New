#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QFileSystemModel>

#include "EWFileExplorerTreeView.h"
#include "EWDirectoryHistoryBar.h"

class EWFileExplorer : public QWidget
{
    QVBoxLayout* vMainLayout;
    QSplitter* hSplitter;

    QFileInfo rootDir;
    QFileSystemModel* fileModel;
    EWFileExplorerTreeView* treeView;
    EWDirectoryHistoryBar* dirHistoryBar;

public:
    EWFileExplorer(QWidget* parent = nullptr);
    ~EWFileExplorer() {}

    void startup();

    EWFileExplorerTreeView* getTreeView() const { return treeView; }
    EWDirectoryHistoryBar* getDirHistoryBar() const  { return dirHistoryBar; }

private:
    void setup();
};

