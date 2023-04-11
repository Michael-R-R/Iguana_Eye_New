#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QLabel>

#include "EWGlslEditorMenuBar.h"
#include "EWGlslSrcEditor.h"

class AppStartEvent;

class EWGlslEditor : public QWidget
{
    Q_OBJECT

    QVBoxLayout* vMainLayout;
    QSplitter* vSplitter;
    QSplitter* hSplitter;
    bool isVerticalView;

    EWGlslEditorMenuBar* menuBar;
    QLabel* currShaderNameLabel;
    QLabel* currShaderPathLabel;
    EWGlslSrcEditor* vSrcEditor;
    EWGlslSrcEditor* fSrcEditor;

public:
    EWGlslEditor(QWidget* parent = nullptr);
    ~EWGlslEditor();

    void startup(const AppStartEvent& event);
    void openGlslFile(const QString& path);

    QString getCurrShaderName() const;
    QString getCurrShaderPath() const;
    QString getVertexSource() const;
    QString getFragmentSource() const;

    QLabel* getCurrShaderNameLabel() const { return currShaderNameLabel; }
    QLabel* getCurrShaderPathLabel() const { return currShaderPathLabel; }
    EWGlslSrcEditor* getVertSrcEditor() const { return vSrcEditor; }
    EWGlslSrcEditor* getFragSrcEditor() const { return fSrcEditor; }

public slots:
    void openGlslFileSlot(const unsigned long long key, const QString& path);
    void glslRemovedSlot(const unsigned long long key);
    void glslRenamedSlot(const unsigned long long oldKey, const unsigned long long newKey);
    void clear();
    void changeView();

private:
    void setup();

signals:
    void glslPathChanged(const QString& path);
};

