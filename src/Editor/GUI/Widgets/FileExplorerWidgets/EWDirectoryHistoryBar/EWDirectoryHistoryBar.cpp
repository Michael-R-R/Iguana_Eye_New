#include "EWDirectoryHistoryBar.h"
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
}

void EWDirectoryHistoryBar::addDirectory(const QString& path)
{
    QString name = IEFile::extractName(path);
    int index = historyList.size();

    auto button = new EWDirectoryButton(name, path, index, this);
    connect(button, &EWDirectoryButton::historyButtonClicked, this, &EWDirectoryHistoryBar::updateHistoryBar);

    historyList.append(button);

    hLayout->insertWidget(historyList.size() - 1, button);
}

void EWDirectoryHistoryBar::updateHistoryBar(const int index)
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
