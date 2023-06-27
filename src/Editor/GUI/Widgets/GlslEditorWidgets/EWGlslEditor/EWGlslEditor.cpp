#include "EWGlslEditor.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEShaderManager.h"
#include "IEShader.h"
#include "IEFile.h"
#include "IEHash.h"

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
    fSrcEditor(new EWGlslSrcEditor("Fragment", this)),
    fileHandler(this)
{
    setup();
}

EWGlslEditor::~EWGlslEditor()
{

}

void EWGlslEditor::startup()
{
    menuBar->startup(this);

    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getScene();
    auto* shaderManager = scene->getShaderManager();
    connect(shaderManager, &IEShaderManager::added, this, &EWGlslEditor::openGlslFileSlot);
    connect(shaderManager, &IEShaderManager::removed, this, &EWGlslEditor::glslRemovedSlot);
    connect(shaderManager, &IEShaderManager::keyChanged, this, &EWGlslEditor::glslRenamedSlot);
}

void EWGlslEditor::newGlslFile(const QString& path)
{
    fileHandler.handleGlslNew(path);
}

void EWGlslEditor::openGlslFile(const QString& path)
{
    fileHandler.handleGlslOpen(path);

    emit glslPathChanged(path);
}

void EWGlslEditor::saveGlslFile()
{
    fileHandler.handleGlslSave(getCurrShaderPath());
}

void EWGlslEditor::saveAsGlslFile(const QString& path)
{
    fileHandler.handleGlslSaveAs(path);
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
    openGlslFile(path);
}

void EWGlslEditor::glslRemovedSlot(const unsigned long long key)
{
    if(key == IEHash::Compute(getCurrShaderPath()))
        clear();
}

void EWGlslEditor::glslRenamedSlot(const unsigned long long, const unsigned long long newKey)
{
    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getScene();
    auto* shaderManager = scene->getShaderManager();
    auto* shader = shaderManager->value<IEShader>(newKey);
    if(!shader)
        return;

    QString path = shader->getName();
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
