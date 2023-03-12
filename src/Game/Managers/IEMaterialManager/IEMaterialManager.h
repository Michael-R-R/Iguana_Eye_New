#pragma once

#include <QDataStream>

#include "IEManager.h"
#include "IESerialize.h"
#include "IEMaterial.h"

class GameStartEvent;

class IEMaterialManager: public IEManager<IEMaterial>
{
    Q_OBJECT

public:
    IEMaterialManager();
    ~IEMaterialManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;

    bool add(const unsigned long long key, std::unique_ptr<IEMaterial> value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

signals:
    void added(const unsigned long long key, const QString& path);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEMaterialManager& manager)
    {
        const auto* resources = manager.getResourceContainer().getResources();

        out << (int)resources->size();

        for(auto& item : *resources)
        {
            if(item.second->getIsEdited() && item.second->getType() == IEResource::Type::Game)
            {
                item.second->setIsEdited(false);
                IESerialize::write<IEMaterial>(item.second->getFilePath(), &(*item.second));
            }

            out << item.second->getFilePath()
                << item.second->getId()
                << item.second->getType();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEMaterialManager& manager)
    {
        int size = 0;
        in >> size;

        QString filePath = "";
        IEResource::Type type;
        std::unique_ptr<IEMaterial> material = nullptr;

        for(int i = 0; i < size; i++)
        {
            in >> filePath >> type;

            if(type != IEResource::Type::Game)
                continue;

            material = std::make_unique<IEMaterial>();
            if(!IESerialize::read<IEMaterial>(filePath, &(*material)))
                continue;

            manager.add(material->getId(), std::move(material));
        }

        return in;
    }
};
