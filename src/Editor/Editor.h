#pragma once

#include <QObject>

#include "EInput.h"
#include "EGUI.h"
#include "EActionManager.h"

class QOpenGLExtraFunctions;
class AppStartEvent;

class Editor : public QObject
{
    Q_OBJECT

    EInput* input;
    EGUI* ui;
    EActionManager* actions;

public:
    Editor(QObject* parent = nullptr);
    ~Editor();

    void init();
    void startup(const AppStartEvent& event);
    void shutdown();

    EInput* getInput() const { return input; }
    EGUI* getUi() const { return ui; }
    EActionManager* getActionManager() const { return actions; }
};
