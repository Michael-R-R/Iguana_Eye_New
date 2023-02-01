#pragma once

#include <QObject>

class AppStartEvent;

class EditorActionManager : public QObject
{

public:
    EditorActionManager(QObject* parent = nullptr);
    ~EditorActionManager();

    void setup(const AppStartEvent& event);
};

