#pragma once

#include <QString>
#include <sol/sol.hpp>

#include "IEScript.h"
#include "IEEntity.h"

class IECamera;

class IECameraScript : public IEScript
{
    sol::function startFunc;
    sol::function updateFunc;
    sol::function updateProjectionFunc;

public:
    IECameraScript(QObject* parent = nullptr);
    IECameraScript(const QString& path, QObject* parent = nullptr);
    IECameraScript(const IECameraScript&) = delete;
    ~IECameraScript();

    bool operator==(const IECameraScript& other) { return IEScript::operator==(other); }
    bool operator!=(const IECameraScript& other) { return IEScript::operator!=(other); }
    bool operator<(const IECameraScript& other) { return IEScript::operator<(other); }
    bool operator>(const IECameraScript& other) { return IEScript::operator>(other); }

    bool initalize(sol::state& lua) override;

    void start(const IEEntity entity) const;
    void update() const;
    void updateProjection(IECamera* camera, const float w, const float h) const;

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

