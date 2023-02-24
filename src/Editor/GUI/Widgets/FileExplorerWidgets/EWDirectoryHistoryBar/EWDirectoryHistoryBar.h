#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QVector>

#include "EWDirectoryButton.h"

class EWFileExplorerTreeView;
class EWFileExplorerListView;

class EWDirectoryHistoryBar : public QWidget
{
    Q_OBJECT

    QWidget* scrollAreaWidget;
    QScrollArea* scrollArea;
    QHBoxLayout* hLayout;
    QVBoxLayout* vLayout;

    QString rootDir;
    QVector<EWDirectoryButton*> historyList;

public:
    EWDirectoryHistoryBar(const QString& root, QWidget* parent = nullptr);
    ~EWDirectoryHistoryBar() {}

    void startup(EWFileExplorerTreeView* treeView, EWFileExplorerListView* listView);
    void addDirectory(const QString& path);

private slots:
    void onHistoryButtonClicked(const int index);
    void buildHistoryBarFromPath(const QString& path);

private:
    void clearHistory();
    bool doesPathExist(const QString& path);

signals:
    void directoryUpdated(const QString& path);
};

