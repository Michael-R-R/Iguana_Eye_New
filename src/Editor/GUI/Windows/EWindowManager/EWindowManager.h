#pragma once

#include <QObject>
#include <QMap>

#include "EWWindow.h"

class AppStartEvent;

class EWindowManager : public QObject
{
    QMap<QString, EWWindow*> windowCollection;

public:
    EWindowManager(QObject* parent = nullptr);
    ~EWindowManager();

    void setup(const AppStartEvent& event);

    void showAll();
    void hideAll();

    bool appendWindow(const QString title, EWWindow* window);
    bool removeWindow(const QString& title);
    EWWindow* getValue(const QString& title) const;
    bool doesExist(const QString& title) const;

    void clear();

private:
    void setupOptionsWindow(const AppStartEvent& event);
};

