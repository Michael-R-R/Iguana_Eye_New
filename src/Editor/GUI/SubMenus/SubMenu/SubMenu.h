#pragma once

#include <QMenu>
#include <QString>
#include <QAction>
#include <map>
#include <memory>

class SubMenu : public QMenu
{
    std::map<QString, std::unique_ptr<QAction>> actionCollection;

public:
    SubMenu(QString title, QWidget* parent = nullptr);
    ~SubMenu();

    bool appendAction(const QString& key, std::unique_ptr<QAction> action);
    bool removeAction(const QString& key);
    bool doesExist(const QString& key);

    QAction* getAction(const QString& key);
};

