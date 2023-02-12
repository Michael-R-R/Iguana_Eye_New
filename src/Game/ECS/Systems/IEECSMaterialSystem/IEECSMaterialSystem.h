#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class ECSOnUpdateEvent;

class IEECSMaterialSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entityList;
        QVector<unsigned long long> materialIdList;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entityList << data.materialIdList;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entityList >> data.materialIdList;
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
    void onPostUpdateFrame() override;
    void onRenderFrame() override;

    QVector<unsigned long long> massReplaceMaterialId(const unsigned long long oldId, const unsigned long long newId);
    QVector<unsigned long long> massPurgeMaterialId(const unsigned long long idToPurge);

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

