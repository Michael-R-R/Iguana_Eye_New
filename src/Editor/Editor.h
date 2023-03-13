#pragma once

#include <QObject>

#include "EInput.h"
#include "EGUI.h"
#include "EWOpenGLViewportDropZone.h"

class AppStartEvent;

class Editor : public QObject
{
    Q_OBJECT

    EInput* input;
    EGUI* ui;
    EWOpenGLViewportDropZone* gameFileDropZone;

public:
    Editor(QObject* parent = nullptr);
    ~Editor();

    void startup(const AppStartEvent& event);
    void shutdown();

    EInput* getInput() const { return input; }
    EGUI* getUi() const { return ui; }
};
