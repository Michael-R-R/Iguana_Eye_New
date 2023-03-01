#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class GameStartEvent;
class ECSOnUpdateEvent;
class IEShaderManager;
class IEShader;

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

    // DOES NOT OWN THIS POINTER
    IEShaderManager* shaderManager;

public:
    IEECSShaderSystem();
    ~IEECSShaderSystem();

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    QVector<unsigned long long> massReplaceShaderId(const unsigned long long oldId, const unsigned long long newId);
    QVector<unsigned long long> massPurgeShaderId(const unsigned long long idToPurge);
    IEShader* getAttachedShader(const int index);

    unsigned long long getShaderId(const int index);
    void setShaderId(const int index, const unsigned long long val);

    friend QDataStream& operator<<(QDataStream& out, const IEECSShaderSystem& system)
    {
        out << system.entityMap << system.data;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSShaderSystem& system)
    {
        in >> system.entityMap >> system.data;
        return in;
    }
};

