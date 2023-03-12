#pragma once

#include <QDataStream>

#include "IEResourceManager.h"
#include "IEMaterial.h"
#include "IEFile.h"
#include "IESerialize.h"

class GameStartEvent;

class IEMaterialManager: public IEResourceManager<IEMaterial>
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
        out << (int)manager.resources.size();

        for(auto& i : manager.resources)
        {
            auto& material = *i.second;

            out << material.getType();

            if(material.getType() != IEResource::Type::Game)
                continue;

            if(material.getIsEdited())
            {
                if(!IEFile::doesPathExist(material.getFilePath()))
                    IEFile::makePath(material.getFilePath());

                if(IESerialize::write<IEMaterial>(material.getFilePath(), &material))
                    material.setIsEdited(false);
            }

            out << material.getFilePath();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEMaterialManager& manager)
    {
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

            auto material = std::make_unique<IEMaterial>();
            if(!IESerialize::read<IEMaterial>(filePath, &(*material)))
                continue;

            manager.add(material->getId(), std::move(material));
        }

        return in;
    }
};
