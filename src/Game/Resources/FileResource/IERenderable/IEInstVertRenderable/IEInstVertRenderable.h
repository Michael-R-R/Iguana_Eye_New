#pragma once

#include "IEInstRenderable.h"

class IEInstVertRenderable : public IEInstRenderable
{

public:
    IEInstVertRenderable(QObject* parent = nullptr);
    IEInstVertRenderable(const QString& path,
                         const uint64_t meID,
                         const uint64_t maID,
                         const uint64_t sID,
                         QObject* parent = nullptr);
    IEInstVertRenderable(IERenderable* parent);
    virtual ~IEInstVertRenderable();

protected:
    bool handleBuild() override;
    bool handleBuildRelease() override;
    bool handleDraw(const QVector<std::any>& args) override;

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

