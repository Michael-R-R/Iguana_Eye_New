#pragma once

#include "IERenderable.h"

class IEVertRenderable : public IERenderable
{
public:
    IEVertRenderable(QObject* parent = nullptr);
    IEVertRenderable(const QString& path, QObject* parent = nullptr);
    IEVertRenderable(IERenderable* parent);
    virtual ~IEVertRenderable();

protected:
    bool handleBuild(const int index) override;
    bool handleBuildRelease(const int index) override;
    void handleDraw(const int index, const QVector<std::any>& args) override;

public:
    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

