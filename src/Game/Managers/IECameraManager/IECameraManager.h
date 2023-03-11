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
    bool add(const unsigned long long key, IECamera* value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

signals:
    void added(const unsigned long long key, const QString& value);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IECameraManager& manager)
    {
        auto& resources = manager.getResourceContainer().getResources();

        out << (int)resources.size();

        for(auto item : resources)
        {
            if(item->getType() == IEResource::Type::Game)
            {
                IESerialize::write<IECamera>(item->getFilePath(), item);
            }

            out << item->getFilePath() << item->getType();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IECameraManager& manager)
    {
        int size = 0;
        in >> size;

        QString filePath = "";
        IEResource::Type type;
        IECamera* camera = nullptr;

        for(int i = 0; i < size; i++)
        {
            in >> filePath >> type;

            if(type != IEResource::Type::Game)
                continue;

            camera = new IECamera();
            if(!IESerialize::read<IECamera>(filePath, camera))
            {
                delete camera;
                continue;
            }

            manager.add(camera->getId(), camera);
        }

        return in;
    }
};

