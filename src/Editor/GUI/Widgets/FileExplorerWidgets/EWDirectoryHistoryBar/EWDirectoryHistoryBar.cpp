#include "EWDirectoryHistoryBar.h"
#include "EWFileExplorerTreeView.h"
#include "EWFileExplorerListView.h"
#include "IEFile.h"

EWDirectoryHistoryBar::EWDirectoryHistoryBar(const QString& root, QWidget* parent) :
    QWidget(parent),
    scrollAreaWidget(new QWidget(this)),
    scrollArea(new QScrollArea(this)),
    hLayout(new QHBoxLayout(scrollAreaWidget)),
    vLayout(new QVBoxLayout(this)),
    rootDir(root),
    historyList()
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    scrollArea->setWidget(scrollAreaWidget);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);

    hLayout->setSpacing(20);
    hLayout->addStretch(1);

    vLayout->addWidget(scrollArea);

    this->addDirectory(rootDir);
}

void EWDirectoryHistoryBar::startup(EWFileExplorerTreeView* treeView, EWFileExplorerListView* listView)
{
    connect(treeView, &EWFileExplorerTreeView::folderDoubleClicked, this, &EWDirectoryHistoryBar::buildHistoryBarFromPath);
    connect(listView, &EWFileExplorerListView::folderDoubleClicked, this, &EWDirectoryHistoryBar::addDirectory);
}

void EWDirectoryHistoryBar::addDirectory(const QString& path)
{
    if(path.isEmpty())
        return;
    if(doesPathExist(path))
        return;

    QString name = IEFile::extractName(path);
    int index = historyList.size();

    auto button = new EWDirectoryButton(name, path, index, this);
    connect(button, &EWDirectoryButton::historyButtonClicked, this, &EWDirectoryHistoryBar::onHistoryButtonClicked);

    historyList.append(button);

    hLayout->insertWidget(historyList.size() - 1, button);
}

void EWDirectoryHistoryBar::onHistoryButtonClicked(const int index)
{
    for(int i = index + 1; i < historyList.size(); i++)
    {
        auto temp = historyList[i];
        historyList[i] = nullptr;
        delete temp;
    }

    historyList.erase(historyList.constBegin() + (index + 1), historyList.constEnd());

    emit directoryUpdated(historyList[index]->getDirPath());
}

void EWDirectoryHistoryBar::buildHistoryBarFromPath(const QString& path)
{
    if(doesPathExist(path))
        return;

    clearHistory();

    int startIndex = path.indexOf("root/Content");
    int nextIndex = path.indexOf("/", startIndex);
    int nextNextIndex = path.indexOf("/", nextIndex + 1);

    while(nextIndex > 0)
    {
        QString tempPath = path.mid(0, nextNextIndex);
        if(!doesPathExist(tempPath))
        {
            this->addDirectory(tempPath);
        }

        nextIndex = path.indexOf("/", nextIndex + 1);
        nextNextIndex = path.indexOf("/", nextIndex + 1);
    }
}

void EWDirectoryHistoryBar::clearHistory()
{
    for(int i = 1; i < historyList.size(); i++)
    {
        auto temp = historyList[i];
        historyList[i] = nullptr;
        delete temp;
    }

    historyList.erase(historyList.constBegin() + 1, historyList.constEnd());
}

bool EWDirectoryHistoryBar::doesPathExist(const QString& path)
{
    int size = historyList.size();
    if(size < 1)
        return false;

    return (historyList[size - 1]->getDirPath() == path);
}
