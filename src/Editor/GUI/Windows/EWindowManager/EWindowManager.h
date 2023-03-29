#pragma once

#include <QObject>
#include <QMap>

#include "EWindow.h"

class AppStartEvent;

class EWindowManager : public QObject
{
    QMap<QString, EWindow*> windowCollection;

public:
    EWindowManager(QObject* parent = nullptr);
    ~EWindowManager();

    void startup(const AppStartEvent& event);

    void showAll();
    void hideAll();

    bool appendWindow(const QString title, EWindow* window);
    bool removeWindow(const QString& title);
    EWindow* getValue(const QString& title) const;
    bool doesExist(const QString& title) const;

    void clear();

private:
    void setupOptionsWindow(const AppStartEvent& event);
    void setupGlslEditorWindow(const AppStartEvent& event);
    void setupFileExplorerWindow(const AppStartEvent& event);
    void setupMessageLogWindow(const AppStartEvent& event);
};

