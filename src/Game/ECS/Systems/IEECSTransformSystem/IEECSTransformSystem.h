#pragma once

#include <QDataStream>
#include <QMap>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>

#include "IEECSSystem.h"

class GameStartEvent;
class ECSOnUpdateEvent;
class IEECSHierarchySystem;
class IERenderableManager;

class IEECSTransformSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<QVector3D> position;
        QVector<QVector3D> rotation;
        QVector<QVector3D> scale;
        QVector<QMatrix4x4> transform;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.position << data.rotation
                << data.scale << data.transform;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.position >> data.rotation
               >> data.scale >> data.transform;
            return in;
        }
    };

    Data data;

    QMap<IEEntity, int> dirtyParents; // Dirty entity, index of data

    // DOES NOT OWN THESE POINTERS
    IERenderableManager* renderableManager;

public:
    IEECSTransformSystem();
    ~IEECSTransformSystem();

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    const QVector3D& getPosition(const int index) const;
    const QVector3D& getRotation(const int index) const;
    const QVector3D& getScale(const int index) const;
    const QMatrix4x4& getTransform(const int index) const;

    void setPosition(const int index, const QVector3D& val);
    void setRotation(const int index, const QVector3D& val);
    void setScale(const int index, const QVector3D& val);
    void setTransform(const int index, const QMatrix4x4& val);

private:
    void updateTransform(const int index,
                         QMap<IEEntity, int>& dirtyChildren,
                         const IEECSHierarchySystem* hierarchySystem);
    QMatrix4x4 calcModelMatrix(const int index);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEECSTransformSystem& system)
    {
        out << system.entityMap << system.data;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSTransformSystem& system)
    {
        in >> system.entityMap >> system.data;
        return in;
    }
};

