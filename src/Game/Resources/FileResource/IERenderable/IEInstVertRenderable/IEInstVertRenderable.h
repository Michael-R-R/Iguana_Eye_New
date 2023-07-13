#pragma once

#include "IEInstRenderable.h"

class IEInstVertRenderable : public IEInstRenderable
{

public:
    IEInstVertRenderable(QObject* parent = nullptr);
    IEInstVertRenderable(const QString& path, QObject* parent = nullptr);
    IEInstVertRenderable(IERenderable* parent);
    virtual ~IEInstVertRenderable();

protected:
    bool handleBuild(const int index) override;
    bool handleBuildRelease(const int index) override;
    void handleDraw(const int index, const QVector<std::any>& args) override;

public:
    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

