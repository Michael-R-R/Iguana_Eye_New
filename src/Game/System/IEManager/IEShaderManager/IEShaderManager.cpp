#include "IEShaderManager.h"
#include "IEShader.h"
#include "IEGlslImport.h"
#include "IEFile.h"
#include "IESerialize.h"

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
    QString path = IEFile::absolutePath("./resources/shaders/game/default.glsl");
    auto* shader = new IEShader(this);
    IEGlslImport::importPath(path, *shader);
    defaultID = shader->getID();
    if(!add(shader->getID(), shader))
        delete shader;
}

QDataStream& IEShaderManager::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEResourceManager::serialize(out, obj);

    const auto& manager = static_cast<const IEShaderManager&>(obj);

    out << (int)manager.resources.size();

    foreach(auto* i, manager.resources)
    {
        out << i->getName();

        IESerialize::write<IEShader>(i->getName(), static_cast<IEShader*>(i));
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

    QString path = "";
    for(int i = 0; i < count; i++)
    {
        in >> path;

        auto* shader = new IEShader(&manager);
        if(!IESerialize::read<IEShader>(path, shader))
        {
            delete shader;
            continue;
        }

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
