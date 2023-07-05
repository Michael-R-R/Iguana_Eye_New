#pragma once

#include <QVector>

#include "IEInstRenderable.h"

class IEIndexBufferObject;

class IEInstIndexRenderable : public IEInstRenderable
{
    IEIndexBufferObject* IBO;

public:
    IEInstIndexRenderable(QObject* parent = nullptr);
    IEInstIndexRenderable(const QString& path,
                          const uint64_t meID,
                          const uint64_t maID,
                          const uint64_t sID,
                          QObject* parent = nullptr);
    IEInstIndexRenderable(IERenderable* parent);
    virtual ~IEInstIndexRenderable();

protected:
    bool handleBuild() override;
    bool handleBuildRelease() override;
    bool handleDraw(const QVector<std::any>& args) override;

public:
    void addIBO(IEIndexBufferObject* ibo);

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

