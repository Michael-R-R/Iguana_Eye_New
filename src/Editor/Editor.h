#pragma once

#include <QWidget>

class EInput;
class EGUI;
class EWOpenGLViewportDropZone;

class Editor : public QWidget
{
    Q_OBJECT

    EInput* input;
    EGUI* ui;
    EWOpenGLViewportDropZone* viewportDropZone;

public:
    Editor(QWidget* parent = nullptr);
    ~Editor();

    void startup();
    void shutdown();

    EInput* getInput() const { return input; }
    EGUI* getUi() const { return ui; }
};
