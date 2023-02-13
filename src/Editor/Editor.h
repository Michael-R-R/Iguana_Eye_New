#pragma once

#include <QObject>

#include "EditorInput.h"
#include "EditorUi.h"
#include "EditorActionManager.h"

class QOpenGLExtraFunctions;
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

    void onRenderFrame();

    EditorInput* getInput() const { return input; }
    EditorUi* getUi() const { return ui; }
    EditorActionManager* getActionManager() const { return actions; }
};

