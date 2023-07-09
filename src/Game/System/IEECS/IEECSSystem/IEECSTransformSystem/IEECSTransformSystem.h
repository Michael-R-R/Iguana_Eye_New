#pragma once

#include <QDataStream>
#include <QMap>
#include <QVector>
#include <QSet>
#include <glm/glm.hpp>

#include "IEECSSystem.h"
#include "IESerializeConverter.h"

class IEGame;
class IEECSHierarchySystem;
class IEECSRenderableSystem;
class IERenderableManager;

class IEECSTransformSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<glm::vec3> position;
        QVector<glm::vec4> rotation;
        QVector<glm::vec3> scale;
        QVector<glm::mat4> transform;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            IESerializeConverter::write(out, data.position);
            IESerializeConverter::write(out, data.rotation);
            IESerializeConverter::write(out, data.scale);
            IESerializeConverter::write(out, data.transform);

            out << data.entity;

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            IESerializeConverter::read(in, data.position);
            IESerializeConverter::read(in, data.rotation);
            IESerializeConverter::read(in, data.scale);
            IESerializeConverter::read(in, data.transform);

            in >> data.entity;

            return in;
        }
    };

    Data data;

    QSet<int> dirtyParentIndices;

    IEECSHierarchySystem* hSystem;
    IEECSRenderableSystem* rSystem;
    IERenderableManager* renderableManager;

public:
    IEECSTransformSystem(QObject* parent = nullptr);
    ~IEECSTransformSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void startUp(const IEGame& game) override;
    void shutdown(const IEGame& game) override;
    void onUpdateFrame() override;

    const glm::vec3& getPosition(const int index) const;
    const glm::vec4& getRotation(const int index) const;
    const glm::vec3& getScale(const int index) const;
    const glm::mat4& getTransform(const int index) const;
    const Data& getData() const { return data; }

    void setPosition(const int index, const glm::vec3& val);
    void setRotation(const int index, const glm::vec3& val);
    void setRotation(const int index, const glm::vec4& val);
    void setScale(const int index, const glm::vec3& val);

private:
    void updateTransform(const int index,
                         QSet<int>& dirtyChildren);
    glm::mat4 calcModelMatrix(const int index);

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};

