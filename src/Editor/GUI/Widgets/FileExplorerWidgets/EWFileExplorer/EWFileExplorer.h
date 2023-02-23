#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>

#include "EWDirectoryHistoryBar.h"

class EWFileExplorer : public QWidget
{
    QVBoxLayout* vMainLayout;
    QSplitter* hSplitter;

    QString rootDirStr;
    EWDirectoryHistoryBar* dirHistoryBar;

public:
    EWFileExplorer(QWidget* parent = nullptr);
    ~EWFileExplorer() {}

    void startup();

    EWDirectoryHistoryBar* getDirHistoryBar() const  { return dirHistoryBar; }

private:
    void setup();
};

