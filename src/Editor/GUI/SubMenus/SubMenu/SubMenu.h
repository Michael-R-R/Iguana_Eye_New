#pragma once

#include <QMenu>
#include <QString>
#include <QMap>
#include <QAction>

class SubMenu : public QMenu
{
    QMap<QString, QAction*> actionCollection;

public:
    SubMenu(QString title, QWidget* parent = nullptr);
    virtual ~SubMenu();

    bool appendAction(const QString title, QAction* action);
    bool removeAction(const QString& title);
    bool doesExist(const QString& title);

    QAction* getAction(const QString& title);

    void setAllEnabled(bool val);
};

