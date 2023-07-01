#pragma once

#include <QHash>
#include <QVector>
#include <QVector4D>

#include "IEFileResource.h"
#include "IEUniformData.h"
#include "IEEnum.h"

class IEShader;

class IEMaterial : public IEFileResource
{
protected:
    QHash<IEColorType, QVector<QVector4D>> colors;
    QHash<IETextureType, QVector<uint64_t>> textureIDs;
    IEUniformData uData;

public:
    IEMaterial(QObject* parent = nullptr);
    IEMaterial(const QString& path, QObject* parent = nullptr);
    IEMaterial(const IEMaterial&) = delete;
    virtual ~IEMaterial();

    bool operator==(const IEMaterial& other) { return IEResource::operator==(other); }
    bool operator!=(const IEMaterial& other) { return IEResource::operator!=(other); }
    bool operator<(const IEMaterial& other) { return IEResource::operator<(other); }
    bool operator>(const IEMaterial& other) { return IEResource::operator>(other); }

    void appendColor(IEColorType type, const QVector4D& val);
    void removeColor(IEColorType type, const int index);
    void setColor(IEColorType type, const int index, const QVector4D& val);
    void appendTextureID(IETextureType type, const uint64_t val);
    void removeTextureID(IETextureType type, const int index);
    void setTextureID(IETextureType type, const int index, const uint64_t val);
    void bindData(IEShader& shader) const;

    const QHash<IEColorType, QVector<QVector4D>>& getColors() const;
    const QHash<IETextureType, QVector<uint64_t>>& getTexIDs() const;
    IEUniformData& getUniformData();

    void setUniformData(const IEUniformData& val);

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;

private:
    void setup();
};
