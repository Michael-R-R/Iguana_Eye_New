#include "IEShaderManager.h"
#include "IEGlslImporter.h"

IEShaderManager::IEShaderManager() :
    IEResourceManager()
{

}

IEShaderManager::~IEShaderManager()
{

}

bool IEShaderManager::add(const unsigned long long key, std::unique_ptr<IEShader> value)
{
    if(!value || doesExist(key))
        return false;

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

        out << shader.getFilePath() << shader.getId();
    }

    return out;
}

QDataStream& IEShaderManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IEShaderManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    QString path = "";
    unsigned long long id = 0;

    for(int i = 0; i < size; i++)
    {
        in >> path >> id;

        auto shader = std::make_unique<IEShader>(path, id);
        if(!IEGlslImporter::importGlsl(path, *shader))
            continue;

        shader->build();
        manager.add(id, std::move(shader));
    }

    return in;
}
