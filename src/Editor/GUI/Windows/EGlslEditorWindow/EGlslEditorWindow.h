#pragma once

#include "EWindow.h"
#include "EWGlslEditor.h"

class AppStartEvent;

class EGlslEditorWindow : public EWindow
{
    Q_OBJECT

    std::unique_ptr<EWGlslEditor> glslEditorWidget;

public:
    EGlslEditorWindow(QWidget* parent = nullptr);
    ~EGlslEditorWindow() {}

    void startup(const AppStartEvent& event);
};

