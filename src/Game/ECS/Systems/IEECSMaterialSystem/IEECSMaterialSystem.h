#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class IEMaterialManager;
class IEMaterial;
class ECSOnUpdateEvent;

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

public:
    IEECSMaterialSystem();
    ~IEECSMaterialSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    QVector<unsigned long long> massReplaceMaterialId(const unsigned long long oldId, const unsigned long long newId);
    QVector<unsigned long long> massPurgeMaterialId(const unsigned long long idToPurge);
    IEMaterial* getAttachedMaterial(const int index);

    unsigned long long getMaterialId(const int index);
    void setMaterialId(const int index, const unsigned long long val);

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

