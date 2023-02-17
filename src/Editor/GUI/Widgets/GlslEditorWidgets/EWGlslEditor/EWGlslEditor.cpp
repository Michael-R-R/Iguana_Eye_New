#include "EWGlslEditor.h"
#include "AppStartEvent.h"

EWGlslEditor::EWGlslEditor(QWidget* parent) :
    QWidget(parent),
    vMainLayout(new QVBoxLayout(this)),
    vSplitter(new QSplitter(Qt::Vertical, this)),
    hSplitter(new QSplitter(this)),
    isVerticalView(true),
    menuBar(new EWGlslEditorMenuBar(this)),
    shaderComboBox(new EWShaderComboBox(this)),
    vSrcEditor(new EWGlslSrcEditor("Vertex", this)),
    fSrcEditor(new EWGlslSrcEditor("Fragment", this))
{
    setup();
}

void EWGlslEditor::startup(const AppStartEvent& event)
{
    menuBar->startup(event, this);
    shaderComboBox->startup(event);
}

void EWGlslEditor::changeView()
{
    if(isVerticalView)
    {
        hSplitter->addWidget(vSrcEditor);
        hSplitter->addWidget(fSrcEditor);
    }
    else
    {
        vSplitter->insertWidget(1, vSrcEditor);
        vSplitter->insertWidget(2, fSrcEditor);
    }

    isVerticalView = !isVerticalView;
}

void EWGlslEditor::setup()
{
    vMainLayout->addWidget(menuBar);
    vMainLayout->addWidget(shaderComboBox);
    vMainLayout->addWidget(vSplitter);

    vSplitter->addWidget(hSplitter);
    vSplitter->addWidget(vSrcEditor);
    vSplitter->addWidget(fSrcEditor);
}
