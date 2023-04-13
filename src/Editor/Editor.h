#pragma once

#include <QObject>

class EInput;
class EGUI;
class EWOpenGLViewportDropZone;

class Editor : public QObject
{
    Q_OBJECT

    EInput* input;
    EGUI* ui;
    EWOpenGLViewportDropZone* viewportDropZone;

public:
    Editor(QObject* parent = nullptr);
    ~Editor();

    void startup();
    void shutdown();

    EInput* getInput() const { return input; }
    EGUI* getUi() const { return ui; }
};
