#include "EWGlslEditor.h"
#include "AppStartEvent.h"
#include "IEScene.h"
#include "IEShaderManager.h"
#include "IEFile.h"
#include "IEHash.h"
#include "IEGlslImporter.h"

EWGlslEditor::EWGlslEditor(QWidget* parent) :
    QWidget(parent),
    vMainLayout(new QVBoxLayout(this)),
    vSplitter(new QSplitter(Qt::Vertical, this)),
    hSplitter(new QSplitter(this)),
    isVerticalView(true),
    menuBar(new EWGlslEditorMenuBar(this)),
    currShaderNameLabel(new QLabel("", this)),
    currShaderPathLabel(new QLabel("", this)),
    vSrcEditor(new EWGlslSrcEditor("Vertex", this)),
    fSrcEditor(new EWGlslSrcEditor("Fragment", this))
{
    setup();
}

EWGlslEditor::~EWGlslEditor()
{

}

void EWGlslEditor::startup(const AppStartEvent& event)
{
    menuBar->startup(event, this);

    auto& shaderManager = IEScene::instance().getShaderManager();
    connect(&shaderManager, &IEShaderManager::added, this, &EWGlslEditor::openGlslFileSlot);
    connect(&shaderManager, &IEShaderManager::removed, this, &EWGlslEditor::glslRemovedSlot);
    connect(&shaderManager, &IEShaderManager::keyChanged, this, &EWGlslEditor::glslRenamedSlot);
}

void EWGlslEditor::openGlslFile(const QString& path)
{
    QString vSrc = "";
    QString fSrc = "";
    IEGlslImporter::importGlsl(path, vSrc, fSrc);

    QString name = IEFile::extractName(path);
    currShaderNameLabel->setText(name);
    currShaderPathLabel->setText(path);

    vSrcEditor->setTextContent(vSrc);
    fSrcEditor->setTextContent(fSrc);

    emit glslPathChanged(path);
}

QString EWGlslEditor::getCurrShaderName() const
{
    return currShaderNameLabel->text();
}

QString EWGlslEditor::getCurrShaderPath() const
{
    return currShaderPathLabel->text();
}

QString EWGlslEditor::getVertexSource() const
{
    return vSrcEditor->getTextContent();
}

QString EWGlslEditor::getFragmentSource() const
{
    return fSrcEditor->getTextContent();
}

void EWGlslEditor::openGlslFileSlot(const unsigned long long, const QString& path)
{
    if(!getCurrShaderPath().isEmpty())
    {
        // TODO ask to save file if needed
    }

    openGlslFile(path);
}

void EWGlslEditor::glslRemovedSlot(const unsigned long long key)
{
    if(key == IEHash::Compute(getCurrShaderPath()))
        clear();
}

void EWGlslEditor::glslRenamedSlot(const unsigned long long, const unsigned long long newKey)
{
    auto& shaderManager = IEScene::instance().getShaderManager();
    auto shader = shaderManager.value(newKey);
    if(!shader)
        return;

    QString path = shader->getFilePath();
    QString name = IEFile::extractName(path);
    currShaderNameLabel->setText(name);
    currShaderPathLabel->setText(path);
}

void EWGlslEditor::clear()
{
    currShaderNameLabel->clear();
    currShaderPathLabel->clear();
    vSrcEditor->clear();
    fSrcEditor->clear();

    emit glslPathChanged("");
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
    currShaderNameLabel->setMinimumSize(1, 16);
    currShaderPathLabel->setMinimumSize(1, 16);

    vMainLayout->addWidget(menuBar);
    vMainLayout->addWidget(currShaderNameLabel);
    vMainLayout->addWidget(currShaderPathLabel);
    vMainLayout->addWidget(vSplitter);

    vSplitter->addWidget(hSplitter);
    vSplitter->addWidget(vSrcEditor);
    vSplitter->addWidget(fSrcEditor);
}
