#include "IERenderableManager.h"
#include "IEScene.h"
#include "IEShaderManager.h"
#include "IESerialize.h"
#include "IEFile.h"

IERenderableManager::IERenderableManager() :
    IEResourceManager()
{

}

IERenderableManager::~IERenderableManager()
{

}

bool IERenderableManager::add(const unsigned long long key, std::unique_ptr<IERenderable> value)
{
    if(!value || doesExist(key))
        return false;

    emit added(key, value->getFilePath());

    resources[key] = std::move(value);

    return true;
}

bool IERenderableManager::remove(const unsigned long long key)
{
    if(!doesExist(key))
        return false;

    resources.erase(key);

    emit removed(key);

    return true;
}

bool IERenderableManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!doesExist(oldKey) || doesExist(newKey))
        return false;

    auto temp = std::move(resources.at(oldKey));
    resources.erase(oldKey);
    resources[newKey] = std::move(temp);

    emit keyChanged(oldKey, newKey);

    return true;
}

QDataStream& IERenderableManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IERenderableManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : manager.resources)
    {
        out << *i.second;
    }

    return out;
}

QDataStream& IERenderableManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IERenderableManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    for(int i = 0; i < size; i++)
    {
        auto renderable = std::make_unique<IERenderable>();

        in >> *renderable;

        auto& shaderManager = IEScene::instance().getShaderManager();
        IEShader* shader = shaderManager.value(renderable->getShaderId());
        renderable->build(*shader);

        auto id = renderable->getId();
        manager.add(id, std::move(renderable));
    }

    return in;
}
