#pragma once

#include <QObject>

#include "EditorInput.h"
#include "EditorUi.h"
#include "EditorActionManager.h"

class AppStartEvent;

class Editor : public QObject
{
    Q_OBJECT

    EditorInput* input;
    EditorUi* ui;
    EditorActionManager* actions;

public:
    Editor(QObject* parent = nullptr);
    ~Editor();

    void startup(const AppStartEvent& event);
    void shutdown();

    EditorInput* getInput() { return input; }
    EditorUi* getUi() { return ui; }
    EditorActionManager* getActionManager() { return actions; }
};

