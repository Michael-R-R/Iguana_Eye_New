#pragma once

#include "IERenderable.h"

class IEIndexBufferObject;

class IEIndexRenderable : public IERenderable
{
protected:
    IEIndexBufferObject* IBO;

public:
    IEIndexRenderable(QObject* parent = nullptr);
    IEIndexRenderable(const QString& path,
                      const uint64_t meID,
                      const uint64_t maID,
                      const uint64_t sID,
                      QObject* parent = nullptr);
    IEIndexRenderable(IERenderable* parent);
    virtual ~IEIndexRenderable();

protected:
    bool handleBuild() override;
    bool handleBuildRelease() override;
    bool handleDraw(const QVector<std::any>& args) override;

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

