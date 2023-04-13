#pragma once

#include <QSharedPointer>
#include <QListView>

#include "EWFileExplorerView.h"

class EWFileExplorerListView : public QListView, public EWFileExplorerView
{
    Q_OBJECT

public:
    EWFileExplorerListView(QFileSystemModel* model, QWidget* parent = nullptr);
    ~EWFileExplorerListView() {}

    void startup(const QModelIndex rootIndex) override;
    QString getCurrentDirectory() override;

protected slots:
    void onDoubleClicked(QModelIndex index) override;

signals:
    void folderDoubleClicked(const QString& path);
};

