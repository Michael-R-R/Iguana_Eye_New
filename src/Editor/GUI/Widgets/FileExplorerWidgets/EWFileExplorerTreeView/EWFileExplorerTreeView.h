#pragma once

#include <QTreeView>

#include "EWFileExplorerView.h"

class EWFileExplorerTreeView : public QTreeView, public EWFileExplorerView
{
    Q_OBJECT

public:
    EWFileExplorerTreeView(QFileSystemModel* model, QWidget* parent = nullptr);
    ~EWFileExplorerTreeView() {}

    void startup(const QModelIndex rootIndex) override;
    QString getCurrentDirectory() override;

protected slots:
    void onDoubleClicked(QModelIndex index) override;

signals:
    void folderDoubleClicked(const QString& path);
};

