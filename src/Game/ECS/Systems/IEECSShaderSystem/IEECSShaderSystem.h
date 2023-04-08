#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class IEShader;
class ECSOnUpdateEvent;

class IEECSShaderSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<unsigned long long> shaderId;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.shaderId;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.shaderId;
            return in;
        }
    };

    Data data;

public:
    IEECSShaderSystem();
    ~IEECSShaderSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    QVector<unsigned long long> massReplaceShaderId(const unsigned long long oldId, const unsigned long long newId);
    QVector<unsigned long long> massPurgeShaderId(const unsigned long long idToPurge);
    QSharedPointer<IEShader> getAttachedShader(const int index) const;

    unsigned long long getShaderId(const int index) const;
    void setShaderId(const int index, const unsigned long long val);

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

