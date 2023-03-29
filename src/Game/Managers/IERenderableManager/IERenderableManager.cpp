#include "IERenderableManager.h"
#include "GameStartEvent.h"
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

void IERenderableManager::startup(const GameStartEvent& event)
{
    this->buildAllRenderables(event);
}

void IERenderableManager::shutdown()
{
    clear();
}

bool IERenderableManager::add(const unsigned long long key, std::unique_ptr<IERenderable> value)
{
    if(!value || doesExist(key))
        return false;

    if(value->getType() == IEResource::Type::Game)
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

void IERenderableManager::buildAllRenderables(const GameStartEvent& event)
{
    auto& shaderManager = event.getScene().getShaderManager();

    for(auto& i : resources)
    {
        auto& renderable = *i.second;

        auto* shader = shaderManager.value(renderable.getShaderId());
        if(!shader)
            continue;

        renderable.build(*shader);
    }
}

QDataStream& IERenderableManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IERenderableManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : manager.resources)
    {
        auto& renderable = *i.second;

        out << renderable.getType();

        if(renderable.getType() != IEResource::Type::Game)
            continue;

        if(renderable.getIsEdited())
        {
            if(!IEFile::doesPathExist(renderable.getFilePath()))
                IEFile::makePath(renderable.getFilePath());

            if(IESerialize::write<IERenderable>(renderable.getFilePath(), &renderable))
                renderable.setIsEdited(false);
        }

        out << renderable.getFilePath();
    }

    return out;
}

QDataStream& IERenderableManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IERenderableManager&>(obj);

    int size = 0;
    in >> size;

    IEResource::Type type;
    QString filePath = "";

    for(int i = 0; i < size; i++)
    {
        in >> type;

        if(type != IEResource::Type::Game)
            continue;

        in >> filePath;

        auto renderable = std::make_unique<IERenderable>();
        if(!IESerialize::read<IERenderable>(filePath, &(*renderable)))
            continue;

        manager.add(renderable->getId(), std::move(renderable));
    }

    return in;
}
