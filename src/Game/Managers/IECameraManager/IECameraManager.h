#pragma once

#include <QDataStream>

#include "IEResourceManager.h"
#include "IECamera.h"
#include "IESerialize.h"

class IECameraManager : public IEResourceManager<IECamera>
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
        out << (int)manager.resources.size();

        for(auto& i : manager.resources)
        {
            auto& camera = *i.second;

            out << camera.getType();

            if(camera.getType() != IEResource::Type::Game)
                continue;

            out << camera.getFilePath();

            IESerialize::write<IECamera>(camera.getFilePath(), &camera);
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IECameraManager& manager)
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

            auto camera = std::make_unique<IECamera>();
            if(!IESerialize::read<IECamera>(filePath, &(*camera)))
                continue;

            manager.add(camera->getId(), std::move(camera));
        }

        return in;
    }
};

