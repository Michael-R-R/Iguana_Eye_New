#pragma once

#include <QVector>

#include "IEECSSystem.h"
#include "IEScript.h"

class IECamera;
class IECameraManager;
class IEScriptEngine;
class IEECSTransformSystem;

class IEECSCameraSystem : public IEECSSystem
{
    struct Data : public IEObject
    {
        QVector<IEEntity> entity;
        QVector<uint64_t> cameraId;
        QVector<IEScript*> script;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            int size = data.script.size();

            out << data.entity << data.cameraId;
            out << size;

            for(int i = 0; i < size; i++)
            {
                out << *data.script[i];
            }

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            int size = 0;
            in >> data.entity >> data.cameraId >> size;

            data.script.clear();
            for(int i = 0; i < size; i++)
            {
                auto script = new IEScript(&data);

                in >> *script;

                data.script.append(script);
            }

            return in;
        }
    };

    Data data;

    int activeIndex;

    IECameraManager* cameraManager;
    IEScriptEngine* sEngine;
    IEECSTransformSystem* tSystem;

public:
    IEECSCameraSystem(QObject* parent = nullptr);
    ~IEECSCameraSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void startUp(const IEGame& game) override;
    void shutdown(const IEGame& game) override;
    void onDeserialize(const IEGame& game) override;
    void onUpdateFrame() override;

    void initAll();
    void startAll();
    void init(const int index);
    void start(const int index);
    void removeScript(const int index);
    void removeAll();

    int getActiveIndex() const;
    IEEntity getActiveEntity() const;
    IECamera* getActiveCamera() const;
    IECamera* getAttachedCamera(const int index) const;
    void setActiveIndex(const int val);

    const IEScript* getScript(const int index) const;
    uint64_t getCameraId(const int index) const;

    void setScript(const int index, IEScript* val);
    void setCameraId(const int index, const uint64_t val);

private:
    void cacheScripts();
    void decacheScripts();

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};
