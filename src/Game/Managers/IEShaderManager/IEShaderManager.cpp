#include "IEShaderManager.h"
#include "IEGlslImporter.h"

IEShaderManager::IEShaderManager() :
    IEResourceManager()
{

}

IEShaderManager::~IEShaderManager()
{

}

bool IEShaderManager::add(const unsigned long long key, QSharedPointer<IEShader> value)
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

    resources.remove(key);

    emit removed(key);

    return true;
}

bool IEShaderManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!doesExist(oldKey) || doesExist(newKey))
        return false;

    auto temp = resources[oldKey];
    resources.remove(oldKey);
    resources[newKey] = temp;

    emit keyChanged(oldKey, newKey);

    return true;
}

void IEShaderManager::buildAllShaders()
{
    for(auto& i : resources)
    {
        i->build();
    }
}

QDataStream& IEShaderManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IEShaderManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : manager.resources)
    {
        out << *i;
    }

    return out;
}

QDataStream& IEShaderManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IEShaderManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    for(int i = 0; i < size; i++)
    {
        auto shader = QSharedPointer<IEShader>::create();

        in >> *shader;

        shader->build();

        manager.add(shader->getId(), shader);
    }

    return in;
}
