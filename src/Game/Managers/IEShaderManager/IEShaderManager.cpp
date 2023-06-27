#include "IEShaderManager.h"
#include "IEShader.h"
#include "IEFile.h"
#include "IEShaderImport.h"

IEShaderManager::IEShaderManager(QObject* parent) :
    IEResourceManager(parent)
{

}

IEShaderManager::~IEShaderManager()
{

}

void IEShaderManager::startup()
{
    auto shader = new IEShader(IEFile::absolutePath("./resources/shaders/game/default.glsl"), this);
    IEShaderImport::importGlsl(shader->getName(), *shader);
    shader->build();
    defaultId = shader->getId();
    this->add(defaultId, shader);
}

QDataStream& IEShaderManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const IEShaderManager& manager = static_cast<const IEShaderManager&>(obj);

    out << (int)manager.resources.size();

    for(auto* i : manager.resources)
    {
        out << *static_cast<IEShader*>(i);
    }

    return out;
}

QDataStream& IEShaderManager::deserialize(QDataStream& in, Serializable& obj)
{
    IEShaderManager& manager = static_cast<IEShaderManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    IEShader* shader = nullptr;

    for(int i = 0; i < size; i++)
    {
        shader = new IEShader(&manager);

        in >> *shader;

        if(!IEShaderImport::importGlsl(shader->getName(), *shader))
        {
            delete shader;
            continue;
        }

        if(!manager.add(shader->getId(), shader))
            delete shader;
        else
            shader->build();
    }

    return in;
}
