#include "IEShaderManager.h"
#include "GameStartEvent.h"
#include "IEGlslImporter.h"

IEShaderManager::IEShaderManager() :
    IEResourceManager()
{

}

IEShaderManager::~IEShaderManager()
{

}

void IEShaderManager::startup(const GameStartEvent&)
{
    this->buildAllShaders();

    emit message("IEShaderManager Startup Successful");
}

void IEShaderManager::shutdown()
{
    clear();

    emit message("IEShaderManager Shutdown Successful");
}

bool IEShaderManager::add(const unsigned long long key, std::unique_ptr<IEShader> value)
{
    if(!value || doesExist(key))
        return false;

    if(value->getType() == IEResource::Type::Game)
        emit added(key, value->getFilePath());

    resources[key] = std::move(value);

    return true;
}

bool IEShaderManager::remove(const unsigned long long key)
{
    if(!doesExist(key))
        return false;

    resources.erase(key);

    emit removed(key);

    return true;
}

bool IEShaderManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!doesExist(oldKey) || doesExist(newKey))
        return false;

    auto temp = std::move(resources.at(oldKey));
    resources.erase(oldKey);
    resources[newKey] = std::move(temp);

    emit keyChanged(oldKey, newKey);

    return true;
}

void IEShaderManager::buildAllShaders()
{
    for(auto& i : resources)
    {
        i.second->build();
    }
}

QDataStream& IEShaderManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IEShaderManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : manager.resources)
    {
        auto& shader = *i.second;

        out << shader.getType();

        if(shader.getType() != IEResource::Type::Game)
            continue;

        out << shader.getFilePath() << shader.getId();
    }

    return out;
}

QDataStream& IEShaderManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IEShaderManager&>(obj);

    int size = 0;
    in >> size;

    IEResource::Type type;
    QString path = "";
    unsigned long long id = 0;

    for(int i = 0; i < size; i++)
    {
        in >> type;

        if(type != IEResource::Type::Game)
            continue;

        in >> path >> id;

        auto shader = std::make_unique<IEShader>(path, id);
        if(!IEGlslImporter::importGlsl(path, *shader))
            continue;

        manager.add(id, std::move(shader));
    }

    return in;
}
