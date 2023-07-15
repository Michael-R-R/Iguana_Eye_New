#pragma once

#include <QVector>
#include <QHash>

#include "IESystem.h"

class IEResourceManager;

class IEScene : public IESystem
{
    QVector<IESystem*> systems;
    QHash<size_t, int> systemIndices;

public:
    IEScene(QObject* parent = nullptr);
    virtual ~IEScene();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void onSerialize(IEGame& game) override;
    void onDeserialize(IEGame& game) override;

    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;

    template<class T>
    bool appendSystem(IESystem* system)
    {
        if(!system || doesSystemExist<T>())
            return false;

        size_t key = typeid(T).hash_code();
        const int index = systems.size();
        systems.append(system);
        systemIndices.insert(key, index);

        return true;
    }

    template<class T>
    bool doesSystemExist() const
    {
        size_t key = typeid(T).hash_code();
        return systemIndices.contains(key);
    }

    template<class T>
    T* getSystem() const
    {
        if(!doesSystemExist<T>())
            return nullptr;

        size_t key = typeid(T).hash_code();

        return static_cast<T*>(systems[systemIndices[key]]);
    }
};
