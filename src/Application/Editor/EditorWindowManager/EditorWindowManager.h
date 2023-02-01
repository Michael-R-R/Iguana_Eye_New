#pragma once

#include <QObject>
#include <QMap>

#include "Window.h"

class AppStartEvent;

class EditorWindowManager : public QObject
{
    QMap<QString, Window*> windowCollection;

public:
    EditorWindowManager(QObject* parent = nullptr);
    ~EditorWindowManager();

    void setup(const AppStartEvent& event);

    void showAll();
    void hideAll();

    bool appendWindow(const QString title, Window* window);
    bool removeWindow(const QString& title);
    bool doesExist(const QString& title) const;

    Window* getWindow(const QString& title) const;

private:
    void setupOptionsWindow(const AppStartEvent& event);
};

