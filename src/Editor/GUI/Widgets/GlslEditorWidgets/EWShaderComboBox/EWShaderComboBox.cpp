#include "EWShaderComboBox.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "IEFile.h"
#include <QAbstractItemView>

EWShaderComboBox::EWShaderComboBox(QWidget* parent) :
    QComboBox(parent),
    shaderManager(nullptr),
    fullIdList(),
    contextMenu(new ShaderComboBoxContextMenu(this))
{
    this->view()->viewport()->installEventFilter(this);
    this->view()->setContextMenuPolicy(Qt::CustomContextMenu);
    this->addItem("");
    fullIdList.append(0);

    connect(this->view(), &QAbstractItemView::customContextMenuRequested, this, &EWShaderComboBox::showCustomContextMenu);
    connect(this, &EWShaderComboBox::currentIndexChanged, this, &EWShaderComboBox::currentShaderChanged);
}

EWShaderComboBox::~EWShaderComboBox()
{
    shaderManager = nullptr;
}

bool EWShaderComboBox::eventFilter(QObject*, QEvent* event)
{
    if(event->type() == QEvent::MouseButtonRelease)
        if(static_cast<QMouseEvent*>(event)->button() == Qt::RightButton)
            return true;

    return false;
}

void EWShaderComboBox::startup(const AppStartEvent& event)
{
    shaderManager = event.getGame()->getIEScene()->getShaderManager();

    this->initialBuild(shaderManager);

    connect(shaderManager, &IEShaderManager::added, this, &EWShaderComboBox::addShader);
    connect(shaderManager, &IEShaderManager::removed, this, &EWShaderComboBox::removeShader);
    connect(shaderManager, &IEShaderManager::keyChanged, this, &EWShaderComboBox::changeShaderKey);

    this->setCurrentIndex(0);

    contextMenu->startup(shaderManager);
}

void EWShaderComboBox::selectShader(const unsigned long long key)
{
    int index = fullIdList.indexOf(key);
    if(!indexBoundCheck(index))
        return;

    this->setCurrentIndex(index);
}

unsigned long long EWShaderComboBox::getSelectedId()
{
    return fullIdList[this->currentIndex()];
}

void EWShaderComboBox::initialBuild(const IEShaderManager* shaderManager)
{
    auto resources = shaderManager->getResourceContainer()->getResources();
    for(auto item : resources)
    {
        if(item->getType() == IEResource::Type::Editor)
            continue;

        this->addShader(item->getId(), item->getFilePath());
    }
}

bool EWShaderComboBox::indexBoundCheck(const int index)
{
    return (index > 0 && index < fullIdList.size());
}

bool EWShaderComboBox::doesExist(const unsigned long long key)
{
    return (fullIdList.indexOf(key) > -1);
}

void EWShaderComboBox::currentShaderChanged(int index)
{
    if(!indexBoundCheck(index))
    {
        emit cleared();
        return;
    }

    auto resourceId = fullIdList[index];

    const IEShader* shader = shaderManager->getValue(resourceId);
    if(!shader)
    {
        emit cleared();
        return;
    }

    emit vertexSrcSelected(shader->getVertexSrc());
    emit fragmentSrcSelected(shader->getFragmentSrc());
}

void EWShaderComboBox::addShader(const unsigned long long key, const QString& path)
{
    if(doesExist(key))
        return;

    int index = fullIdList.size();

    fullIdList.append(key);

    QString extractedName = IEFile::extractName(path);

    this->addItem(extractedName);
    this->setCurrentIndex(index);
}

void EWShaderComboBox::removeShader(const unsigned long long key)
{
    int index = fullIdList.indexOf(key);
    if(!indexBoundCheck(index))
        return;

    if(index == this->currentIndex())
    {
        emit cleared();
        this->setCurrentIndex(0);
    }

    this->removeItem(index);
    fullIdList.removeAt(index);
}

void EWShaderComboBox::changeShaderKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    int index = fullIdList.indexOf(oldKey);
    if(!indexBoundCheck(index))
        return;

    fullIdList[index] = newKey;

    auto shader = shaderManager->getValue(newKey);
    QString extractedName = IEFile::extractName(shader->getFilePath());

    this->setItemText(index, extractedName);
}

void EWShaderComboBox::showCustomContextMenu(const QPoint& pos)
{
    QModelIndex modelIndex = this->view()->indexAt(pos);
    if(!modelIndex.isValid())
        return;

    int index = modelIndex.row();
    if(!indexBoundCheck(index))
        return;

    unsigned long long id = fullIdList[index];
    contextMenu->setSelectedId(id);
    contextMenu->exec(this->view()->mapToGlobal(pos));
}
