#pragma once

#include <QObject>
#include <QMap>

#include "EWindow.h"

class EWindowManager : public QObject
{
    QMap<QString, EWindow*> windowCollection;

public:
    EWindowManager(QObject* parent = nullptr);
    ~EWindowManager();

    void startup();

    void showAll();
    void hideAll();

    bool appendWindow(const QString title, EWindow* window);
    bool removeWindow(const QString& title);
    EWindow* value(const QString& title) const;
    bool doesExist(const QString& title) const;

    void clear();

private:
    void setupOptionsWindow();
    void setupGlslEditorWindow();
    void setupFileExplorerWindow();
    void setupMessageLogWindow();
};

