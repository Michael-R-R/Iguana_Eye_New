#pragma once

#include "IERenderable.h"

class IEVertRenderable : public IERenderable
{
public:
    IEVertRenderable(QObject* parent = nullptr);
    IEVertRenderable(const QString& path,
                     const uint64_t meID,
                     const uint64_t maID,
                     const uint64_t sID,
                     QObject* parent = nullptr);
    IEVertRenderable(IERenderable* parent);
    virtual ~IEVertRenderable();

protected:
    bool handleBuild() override;
    bool handleBuildRelease() override;
    bool handleDraw(const QVector<std::any>& args) override;

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

