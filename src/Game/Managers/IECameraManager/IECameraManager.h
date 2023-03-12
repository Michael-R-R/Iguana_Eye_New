#pragma once

#include <QDataStream>

#include "IEManager.h"
#include "IECamera.h"
#include "IESerialize.h"

class IECameraManager : public IEManager<IECamera>
{
    Q_OBJECT

public:
    IECameraManager();
    ~IECameraManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;
    bool add(const unsigned long long key, std::unique_ptr<IECamera> value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

signals:
    void added(const unsigned long long key, const QString& path);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IECameraManager& manager)
    {
        const auto* resources = manager.getResourceContainer().getResources();

        out << (int)resources->size();

        for(auto& item : *resources)
        {
            if(item.second->getType() == IEResource::Type::Game)
                IESerialize::write<IECamera>(item.second->getFilePath(), &(*item.second));

            out << item.second->getFilePath()
                << item.second->getId()
                << item.second->getType();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IECameraManager& manager)
    {
        int size = 0;
        in >> size;

        QString filePath = "";
        IEResource::Type type;
        std::unique_ptr<IECamera> camera = nullptr;

        for(int i = 0; i < size; i++)
        {
            in >> filePath >> type;

            if(type != IEResource::Type::Game)
                continue;

            camera = std::make_unique<IECamera>();
            if(!IESerialize::read<IECamera>(filePath, &(*camera)))
                continue;

            manager.add(camera->getId(), std::move(camera));
        }

        return in;
    }
};

