#include "ShaderComboBoxContextMenu.h"
#include "IEShaderManager.h"

ShaderComboBoxContextMenu::ShaderComboBoxContextMenu(QWidget* parent) :
    ContextMenu(parent),
    shaderManager(nullptr),
    selectedId(0)
{

}

ShaderComboBoxContextMenu::~ShaderComboBoxContextMenu()
{
    shaderManager = nullptr;
}

void ShaderComboBoxContextMenu::startup(IEShaderManager* shaderManager)
{
    this->shaderManager = shaderManager;

    setupDeleteShaderAction();
}

void ShaderComboBoxContextMenu::setupDeleteShaderAction()
{
    auto action = new QAction("Delete?", this);
    connect(action, &QAction::triggered, this, [this]()
    {
        shaderManager->remove(selectedId);
    });

    this->addAction(action);
}
