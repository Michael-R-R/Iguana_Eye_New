#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class GameStartEvent;
class ECSOnUpdateEvent;
class IEMaterialManager;
class IEMaterial;

class IEECSMaterialSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<unsigned long long> materialId;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.materialId;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.materialId;
            return in;
        }
    };

    Data data;

    // DOES NOT OWN THIS POINTER
    IEMaterialManager* materialManager;

public:
    IEECSMaterialSystem();
    ~IEECSMaterialSystem();

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    QVector<unsigned long long> massReplaceMaterialId(const unsigned long long oldId, const unsigned long long newId);
    QVector<unsigned long long> massPurgeMaterialId(const unsigned long long idToPurge);
    IEMaterial* getAttachedMaterial(const int index);

    unsigned long long getMaterialId(const int index);
    void setMaterialId(const int index, const unsigned long long val);

    friend QDataStream& operator<<(QDataStream& out, const IEECSMaterialSystem& system)
    {
        out << system.entityMap << system.data;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSMaterialSystem& system)
    {
        in >> system.entityMap >> system.data;
        return in;
    }
};

