#include "IEShaderManager.h"
#include "IEShader.h"
#include "IEFile.h"
#include "IEGlslImport.h"

IEShaderManager::IEShaderManager(QObject* parent) :
    IEResourceManager(parent),
    defaultID(0)
{

}

IEShaderManager::~IEShaderManager()
{

}

void IEShaderManager::startup(IEGame&)
{
    createDefaults();
}

QDataStream& IEShaderManager::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEResourceManager::serialize(out, obj);

    const auto& manager = static_cast<const IEShaderManager&>(obj);

    out << (int)manager.resources.size();

    foreach(auto* i, manager.resources)
    {
        out << *i;
    }

    out << manager.defaultID;

    return out;
}

QDataStream& IEShaderManager::deserialize(QDataStream& in, IESerializable& obj)
{
    IEResourceManager::deserialize(in, obj);

    auto& manager = static_cast<IEShaderManager&>(obj);

    int count = 0;
    in >> count;

    for(int i = 0; i < count; i++)
    {
        auto* shader = new IEShader(&manager);
        in >> *shader;

        if(!shader->build())
        {
            delete shader;
            continue;
        }

        if(!manager.add(shader->getID(), shader))
            delete shader;
    }

    in >> manager.defaultID;

    return in;
}

void IEShaderManager::createDefaults()
{
    QString path = IEFile::absolutePath("./resources/scene/global/shaders/default.glsl");
    auto* shader = new IEShader(this);
    IEGlslImport::importPath(path, *shader);
    defaultID = shader->getID();
    if(!add(shader->getID(), shader))
        delete shader;
}
