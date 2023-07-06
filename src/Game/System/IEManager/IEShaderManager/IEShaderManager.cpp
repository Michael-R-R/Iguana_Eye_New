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

void IEShaderManager::startup(IEGame&)
{
    QString path = "./resources/shaders/game/default.glsl";
    auto* shader = new IEShader(IEFile::absolutePath(path), this);
    IEShaderImport::importShader(shader->getName(), *shader);
    shader->build();
    defaultId = shader->getId();

    this->add(defaultId, shader);
}

QDataStream& IEShaderManager::serialize(QDataStream& out, const IESerializable& obj) const
{
    const IEShaderManager& manager = static_cast<const IEShaderManager&>(obj);

    out << (int)manager.resources.size();

    for(auto* i : qAsConst(manager.resources))
    {
        out << i->getName();
    }

    return out;
}

QDataStream& IEShaderManager::deserialize(QDataStream& in, IESerializable& obj)
{
    IEShaderManager& manager = static_cast<IEShaderManager&>(obj);

    int size = 0;
    in >> size;

    for(int i = 0; i < size; i++)
    {
        QString path = "";

        in >> path;

        auto* shader = new IEShader(path, &manager);

        if(!IEShaderImport::importShader(path, *shader))
        {
            delete shader;
            continue;
        }

        if(manager.add(shader->getId(), shader))
            shader->build();
        else
            delete shader;
    }

    return in;
}
