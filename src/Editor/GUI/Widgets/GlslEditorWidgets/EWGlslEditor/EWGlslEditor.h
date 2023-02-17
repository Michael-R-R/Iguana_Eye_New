#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>

#include "EWGlslEditorMenuBar.h"
#include "EWShaderComboBox.h"
#include "EWGlslSrcEditor.h"

class AppStartEvent;

class EWGlslEditor : public QWidget
{
    QVBoxLayout* vMainLayout;
    QSplitter* vSplitter;
    QSplitter* hSplitter;
    bool isVerticalView;

    EWGlslEditorMenuBar* menuBar;
    EWShaderComboBox* shaderComboBox;
    EWGlslSrcEditor* vSrcEditor;
    EWGlslSrcEditor* fSrcEditor;

public:
    EWGlslEditor(QWidget* parent = nullptr);
    ~EWGlslEditor() {}

    void startup(const AppStartEvent& event);

public slots:
    void changeView();

private:
    void setup();
};

