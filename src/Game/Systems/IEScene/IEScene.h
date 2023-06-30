#pragma once

#include <QVector>
#include <QHash>

#include "IEGameSystem.h"

class IEResourceManager;

class IEScene : public IEGameSystem
{
    QVector<IEResourceManager*> managers;
    QHash<size_t, int> managerIndices;

public:
    IEScene(QObject* parent = nullptr);
    ~IEScene();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void onSerialize(IEGame& game) override;
    void onDeserialize(IEGame& game) override;

    bool doesManagerExist(const size_t key) const;

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;

    template<class T>
    bool appendManager(IEResourceManager* manager)
    {
        size_t key = typeid(T).hash_code();
        if(!manager || doesManagerExist(key))
            return false;

        const int index = managers.size();
        managers.append(manager);
        managerIndices.insert(key, index);

        return true;
    }

    template<class T>
    T* getManager()
    {
        size_t key = typeid(T).hash_code();
        if(!doesManagerExist(key))
            return nullptr;

        return static_cast<T*>(managers[managerIndices[key]]);
    }
};
