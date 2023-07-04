#pragma once

#include <QVector>

#include "IEInstRenderable.h"

class IEIndexBufferObject;

class IEInstIndexRenderable : public IEInstRenderable
{
    QVector<IEIndexBufferObject*> IBOs;

public:
    IEInstIndexRenderable(QObject* parent = nullptr);
    IEInstIndexRenderable(const QString& path,
                          const uint64_t mID,
                          const uint64_t sID,
                          QObject* parent = nullptr);
    virtual ~IEInstIndexRenderable();

protected:
    void handleBuild(const int index) override;
    void handleBuildRelease(const int index) override;
    void handleDraw(const int index, const QVector<std::any>& args) override;

public:
    void addIBO(IEIndexBufferObject* ibo);

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

