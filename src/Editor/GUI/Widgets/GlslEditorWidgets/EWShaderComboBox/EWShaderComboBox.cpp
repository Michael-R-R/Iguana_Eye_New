#include "EWShaderComboBox.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "IEFile.h"

EWShaderComboBox::EWShaderComboBox(QWidget* parent) :
    QComboBox(parent),
    nameManager(nullptr), shaderManager(nullptr),
    fullIdList()
{
    this->addItem("");
    fullIdList.append(0);

    connect(this, &EWShaderComboBox::currentIndexChanged, this, &EWShaderComboBox::currentShaderChanged);
}

EWShaderComboBox::~EWShaderComboBox()
{
    nameManager = nullptr;
    shaderManager = nullptr;
}

void EWShaderComboBox::startup(const AppStartEvent& event)
{
    nameManager = event.getGame()->getIEScene()->getNameManager();
    shaderManager = event.getGame()->getIEScene()->getShaderManager();

    // Build combobox with initial values
    for(auto item : shaderManager->getResourceContainer()->getResources())
    {
        this->addShader(item->getId());
    }

    connect(shaderManager, &IEShaderManager::added, this, &EWShaderComboBox::addShader);
    connect(shaderManager, &IEShaderManager::removed, this, &EWShaderComboBox::removeShader);
    connect(shaderManager, &IEShaderManager::keyChanged, this, &EWShaderComboBox::changeShaderKey);
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

void EWShaderComboBox::addShader(const unsigned long long key)
{
    if(doesExist(key))
        return;

    fullIdList.append(key);

    QString resourceName = *nameManager->getValue(key);
    QString extractedName = IEFile::extractFileName(resourceName);

    this->addItem(extractedName);
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

    QString resourceName = *nameManager->getValue(newKey);
    QString extractedName = IEFile::extractFileName(resourceName);

    this->setItemText(index, extractedName);
}
