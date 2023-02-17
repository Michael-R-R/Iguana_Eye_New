#pragma once

#include <QMenuBar>
#include <QMenu>
#include <QString>

#include "SubMenu.h"

class AppStartEvent;

class MainMenuBar : public QMenuBar
{
    QMap<QString, SubMenu*> menuCollection;

public:
    MainMenuBar(QWidget* parent = nullptr);
    ~MainMenuBar();

    void startup(const AppStartEvent& event);

    bool appendSubMenu(QString title, SubMenu* menu);
    bool removeSubMenu(const QString& title);
    bool doesExist(const QString& title);

    SubMenu* getMenu(const QString& title);
    QAction* getMenuAction(const QString& menuTitle, const QString& actionTitle);

private:
    void setupFileSubMenu(const AppStartEvent& event);
    void setupGameSubMenu(const AppStartEvent& event);
    void setupWindowSubMenu(const AppStartEvent& event);
};

