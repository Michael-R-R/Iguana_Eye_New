#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QVector>

#include "EWDirectoryButton.h"

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

    void addDirectory(const QString& path);

private slots:
    void updateHistoryBar(const int index);

signals:
    void directoryUpdated(const QString& path);
};

