#pragma once

#include "EWindow.h"
#include "EWGlslEditor.h"

class EGlslEditorWindow : public EWindow
{
    Q_OBJECT

    EWGlslEditor* glslEditorWidget;

public:
    EGlslEditorWindow(QWidget* parent = nullptr);
    ~EGlslEditorWindow() {}

    void startup() override;

    EWGlslEditor* getGlslEditorWidget() const { return glslEditorWidget; }
};

