#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QVector>

#include "EWDirectoryButton.h"

class EWFileExplorerTreeView;

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

    void startup(EWFileExplorerTreeView* treeView);
    void addDirectory(const QString& path);

private slots:
    void updateHistoryBarFromIndex(const int index);
    void updateHistoryBarFromPath(const QString& path);

private:
    void clearHistory();
    bool doesPathExist(const QString& path);

signals:
    void directoryUpdated(const QString& path);
};

