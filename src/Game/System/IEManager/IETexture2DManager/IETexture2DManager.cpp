#include "IETexture2DManager.h"
#include "IETexture2D.h"

IETexture2DManager::IETexture2DManager(QObject* parent) :
    IEResourceManager(parent)
{

}

IETexture2DManager::~IETexture2DManager()
{

}

QDataStream& IETexture2DManager::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEResourceManager::serialize(out, obj);

    const auto& manager = static_cast<const IETexture2DManager&>(obj);

    out << (int)manager.resources.size();

    foreach (auto* i, manager.resources)
    {
        out << *i;
    }

    return out;
}

QDataStream& IETexture2DManager::deserialize(QDataStream& in, IESerializable& obj)
{
    IEResourceManager::deserialize(in, obj);

    auto& manager = static_cast<IETexture2DManager&>(obj);

    int count = 0;
    in >> count;

    for(int i = 0; i < count; i++)
    {
        auto* texture = new IETexture2D(&manager);
        in >> *texture;

        if(!texture->build())
        {
            delete texture;
            continue;
        }

        if(!manager.add(texture->getID(), texture))
            delete texture;
    }

    return in;
}
