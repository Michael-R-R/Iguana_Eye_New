#pragma once

#include <QObject>

class AppStartEvent;
class EInput;
class EGUI;
class EWOpenGLViewportDropZone;

class Editor : public QObject
{
    Q_OBJECT

    Editor();
    static Editor mInstance;

    EInput* input;
    EGUI* ui;
    EWOpenGLViewportDropZone* viewportDropZone;

public:
    static Editor& instance();
    ~Editor();

    void startup(const AppStartEvent& event);
    void shutdown();

    EInput* getInput() const { return input; }
    EGUI* getUi() const { return ui; }
};
