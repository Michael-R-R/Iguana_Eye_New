#pragma once

#include "IEFileResource.h"
#include "IEUniform.h"

class IEShader;

class IEMaterial : public IEFileResource
{
protected:
    IEUniform uniformData;
    QColor objectColor;
    uint64_t atlasTexId;
    uint64_t diffuseTexId;
    uint64_t specularTexId;
    uint64_t normalTexId;
    uint64_t heightTexId;

public:
    IEMaterial(QObject* parent = nullptr);
    IEMaterial(const QString& path, QObject* parent = nullptr);
    IEMaterial(const IEMaterial&) = delete;
    virtual ~IEMaterial();

    bool operator==(const IEMaterial& other) { return IEResource::operator==(other); }
    bool operator!=(const IEMaterial& other) { return IEResource::operator!=(other); }
    bool operator<(const IEMaterial& other) { return IEResource::operator<(other); }
    bool operator>(const IEMaterial& other) { return IEResource::operator>(other); }

    void bindUniformData(IEShader& shader) const;

    QColor getObjectColor() const { return objectColor; }
    uint64_t getAtlasTexId() const { return atlasTexId; }
    uint64_t getDiffuseTexId() const { return diffuseTexId; }
    uint64_t getSpecularTexId() const { return specularTexId; }
    uint64_t getNormalTexId() const { return normalTexId; }
    uint64_t getHeightTexId() const { return heightTexId; }

    void setUniformData(const IEUniform& val) { uniformData = val; }
    void setObjectColor(const QColor val) { objectColor = val; }
    void setAtlasTexId(const uint64_t val) { atlasTexId = val; }
    void setDiffuseTexId(const uint64_t val) { diffuseTexId = val; }
    void setSpecularTexId(const uint64_t val) { specularTexId = val; }
    void setNormalTexId(const uint64_t val) { normalTexId = val; }
    void setHeightTexId(const uint64_t val) { heightTexId = val; }

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
