#pragma once

#include <QMenuBar>
#include <QMenu>
#include <QString>

#include "SubMenu.h"

class MainMenuBar : public QMenuBar
{
    QMap<QString, SubMenu*> menuCollection;

public:
    MainMenuBar(QWidget* parent = nullptr);
    ~MainMenuBar();

    void startup();
    void shutdown();

    bool appendSubMenu(QString title, SubMenu* menu);
    bool removeSubMenu(const QString& title);
    bool doesExist(const QString& title);

    SubMenu* getMenu(const QString& title);
    QAction* getMenuAction(const QString& menuTitle, const QString& actionTitle);

private:
    void setupFileSubMenu();
    void setupGameSubMenu();
    void setupWindowSubMenu();
};

