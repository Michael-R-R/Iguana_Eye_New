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

    std::unique_ptr<EWGlslEditorMenuBar> menuBar;
    std::unique_ptr<EWShaderComboBox> shaderComboBox;
    std::unique_ptr<EWGlslSrcEditor> vSrcEditor;
    std::unique_ptr<EWGlslSrcEditor> fSrcEditor;

public:
    EWGlslEditor(QWidget* parent = nullptr);
    ~EWGlslEditor() {}

    void startup(const AppStartEvent& event);

    EWShaderComboBox& getShaderComboBox() const { return *shaderComboBox; }
    EWGlslSrcEditor& getVertSrcEditor() const { return *vSrcEditor; }
    EWGlslSrcEditor& getFragSrcEditor() const { return *fSrcEditor; }

public slots:
    void clearAll();
    void changeView();
    void saveContentToFile(const QString& path);

private:
    void setup();
};

