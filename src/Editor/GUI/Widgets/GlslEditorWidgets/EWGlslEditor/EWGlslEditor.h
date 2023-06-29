#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QLabel>

#include "EWGlslEditorMenuBar.h"
#include "EWGlslSrcEditor.h"
#include "GlslFileHandler.h"

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

    GlslFileHandler fileHandler;

public:
    EWGlslEditor(QWidget* parent = nullptr);
    ~EWGlslEditor();

    void startup();

    void newGlslFile(const QString& path);
    void openGlslFile(const QString& path);
    void saveGlslFile();
    void saveAsGlslFile(const QString& path);

    QString getCurrShaderName() const;
    QString getCurrShaderPath() const;
    QString getVertexSource() const;
    QString getFragmentSource() const;

    QLabel* getCurrShaderNameLabel() const { return currShaderNameLabel; }
    QLabel* getCurrShaderPathLabel() const { return currShaderPathLabel; }
    EWGlslSrcEditor* getVertSrcEditor() const { return vSrcEditor; }
    EWGlslSrcEditor* getFragSrcEditor() const { return fSrcEditor; }

public slots:
    void openGlslFileSlot(const uint64_t key, const QString& path);
    void glslRemovedSlot(const uint64_t key);
    void glslRenamedSlot(const uint64_t oldKey, const uint64_t newKey);
    void clear();
    void changeView();

private:
    void setup();

signals:
    void glslFileOpened(const QString& path);
};

