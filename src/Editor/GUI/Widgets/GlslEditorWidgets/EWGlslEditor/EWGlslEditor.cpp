#include "EWGlslEditor.h"
#include "AppStartEvent.h"
#include "IEFile.h"

EWGlslEditor::EWGlslEditor(QWidget* parent) :
    QWidget(parent),
    vMainLayout(new QVBoxLayout(this)),
    vSplitter(new QSplitter(Qt::Vertical, this)),
    hSplitter(new QSplitter(this)),
    isVerticalView(true),
    menuBar(std::make_unique<EWGlslEditorMenuBar>(this)),
    shaderComboBox(std::make_unique<EWShaderComboBox>(this)),
    vSrcEditor(std::make_unique<EWGlslSrcEditor>("Vertex", this)),
    fSrcEditor(std::make_unique<EWGlslSrcEditor>("Fragment", this))
{
    setup();
}

void EWGlslEditor::startup(const AppStartEvent& event)
{
    menuBar->startup(event, this);
    shaderComboBox->startup(event);

    connect(&(*shaderComboBox), &EWShaderComboBox::vertexSrcSelected, &(*vSrcEditor), &EWGlslSrcEditor::setTextContent);
    connect(&(*shaderComboBox), &EWShaderComboBox::fragmentSrcSelected, &(*fSrcEditor), &EWGlslSrcEditor::setTextContent);
    connect(&(*shaderComboBox), &EWShaderComboBox::cleared, this, &EWGlslEditor::clearAll);
}

void EWGlslEditor::clearAll()
{
    shaderComboBox->setCurrentIndex(0);
    vSrcEditor->clear();
    fSrcEditor->clear();
}

void EWGlslEditor::changeView()
{
    if(isVerticalView)
    {
        hSplitter->addWidget(&(*vSrcEditor));
        hSplitter->addWidget(&(*fSrcEditor));
    }
    else
    {
        vSplitter->insertWidget(1, &(*vSrcEditor));
        vSplitter->insertWidget(2, &(*fSrcEditor));
    }

    isVerticalView = !isVerticalView;
}

void EWGlslEditor::saveContentToFile(const QString& path)
{
    QString vSrc = vSrcEditor->getTextContent();
    QString fSrc = fSrcEditor->getTextContent();
    QString content = "[VERTEX]\n" + vSrc + "[FRAGMENT]\n" + fSrc;
    IEFile::write(path, content);

    vSrcEditor->setModifiedStatus(false);
    fSrcEditor->setModifiedStatus(false);
}

void EWGlslEditor::setup()
{
    vMainLayout->addWidget(&(*menuBar));
    vMainLayout->addWidget(&(*shaderComboBox));
    vMainLayout->addWidget(vSplitter);

    vSplitter->addWidget(hSplitter);
    vSplitter->addWidget(&(*vSrcEditor));
    vSplitter->addWidget(&(*fSrcEditor));
}
