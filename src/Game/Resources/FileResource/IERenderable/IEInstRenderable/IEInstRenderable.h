#pragma once

#include <QVector>
#include <QHash>
#include <QPair>
#include <QString>
#include <any>

#include "IERenderable.h"

class IEInstRenderable : public IERenderable
{
protected:
    QVector<QHash<QString, std::any>> hiddenData;
    int shown;
    int hidden;

public:
    IEInstRenderable(IERenderableType ieType, QObject* parent = nullptr);
    IEInstRenderable(IERenderableType ieType,
                     const QString& path,
                     const uint64_t meID,
                     const uint64_t maID,
                     const uint64_t sID,
                     QObject* parent = nullptr);
    IEInstRenderable(const IEInstRenderable&) = delete;
    virtual ~IEInstRenderable();

    bool operator==(const IEInstRenderable& other) { return IERenderable::operator==(other); }
    bool operator!=(const IEInstRenderable& other) { return IERenderable::operator!=(other); }
    bool operator<(const IEInstRenderable& other) { return IERenderable::operator<(other); }
    bool operator>(const IEInstRenderable& other) { return IERenderable::operator>(other); }

protected:
    virtual bool handleBuild() override = 0;
    virtual bool handleBuildRelease() override = 0;
    virtual bool handleDraw(const QVector<std::any>& args) override = 0;

public:
    int addShown();
    int addShown(const int hiddenIndex);
    bool removeShown(const int index);

    int addHidden(const int shownIndex);
    bool removeHidden(const int index);

    QHash<QString, std::any> getInstanceValues(const int shownIndex);
    int getShownCount() const { return shown; }
    int getHiddenCount() const { return hidden; }

protected:
    bool shownIndexBoundsCheck(const int index);
    bool hiddenIndexBoundsCheck(const int index);

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

