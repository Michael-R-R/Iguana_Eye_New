#pragma once

#include <QMenuBar>
#include <QMenu>
#include <QString>
#include <map>

class AppStartEvent;
class SubMenu;

class MainMenuBar : public QMenuBar
{
    std::map<QString, std::unique_ptr<SubMenu>> menuCollection;

public:
    MainMenuBar(QWidget* parent = nullptr);
    ~MainMenuBar();

    void startup(const AppStartEvent& event);

    bool appendSubMenu(const QString& key, std::unique_ptr<SubMenu> value);
    bool removeSubMenu(const QString& key);
    bool doesExist(const QString& key);

    SubMenu* getMenu(const QString& key);
    QAction* getMenuAction(const QString& menuTitle, const QString& actionTitle);

private:
    void setupFileSubMenu(const AppStartEvent& event);
    void setupGameSubMenu(const AppStartEvent& event);
    void setupWindowSubMenu(const AppStartEvent& event);
};

