#pragma once

#include <QObject>
#include <memory>

#include "EInput.h"
#include "EGUI.h"
#include "EWOpenGLViewportDropZone.h"

class AppStartEvent;

class Editor : public QObject
{
    Q_OBJECT

    std::unique_ptr<EInput> input;
    std::unique_ptr<EGUI> ui;
    std::unique_ptr<EWOpenGLViewportDropZone> gameFileDropZone;

public:
    Editor(QObject* parent = nullptr);
    ~Editor();

    void startup(const AppStartEvent& event);
    void shutdown();

    EInput& getInput() const { return *input; }
    EGUI& getUi() const { return *ui; }
};
