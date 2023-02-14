#pragma once

#include <QDataStream>

#include "IEResource.h"
#include "IEUniform.h"

class IEShader;

class IEMaterial : public IEResource
{
protected:
    IEUniform uniformData;
    QColor objectColor;
    unsigned long long atlasTexId;
    unsigned long long diffuseTexId;
    unsigned long long specularTexId;
    unsigned long long normalTexId;
    unsigned long long heightTexId;

public:
    IEMaterial();
    IEMaterial(const unsigned long long id);
    IEMaterial(const IEMaterial& other);
    ~IEMaterial();

    bool operator==(const IEMaterial& other) { return IEResource::operator==(other); }
    bool operator!=(const IEMaterial& other) { return IEResource::operator!=(other); }
    bool operator<(const IEMaterial& other) { return IEResource::operator<(other); }
    bool operator>(const IEMaterial& other) { return IEResource::operator>(other); }

    void bindUniformData(IEShader* shader) const;

    IEUniform& getUniformData() { return uniformData; }
    const QColor getObjectColor() const { return objectColor; }
    const unsigned long long getAtlasTexId() const { return atlasTexId; }
    const unsigned long long getDiffuseTexId() const { return diffuseTexId; }
    const unsigned long long getSpecularTexId() const { return specularTexId; }
    const unsigned long long getNormalTexId() const { return normalTexId; }
    const unsigned long long getHeightTexId() const { return heightTexId; }

    void setUniformData(const IEUniform val) { uniformData = val; }
    void setObjectColor(const QColor val) { objectColor = val; }
    void setAtlasTexId(const unsigned long long val) { atlasTexId = val; }
    void setDiffuseTexId(const unsigned long long val) { diffuseTexId = val; }
    void setSpecularTexId(const unsigned long long val) { specularTexId = val; }
    void setNormalTexId(const unsigned long long val) { normalTexId = val; }
    void setHeightTexId(const unsigned long long val) { heightTexId = val; }

    friend QDataStream& operator<<(QDataStream& out, const IEMaterial& material)
    {
        out << material.id
            << material.uniformData
            << material.objectColor
            << material.atlasTexId
            << material.diffuseTexId
            << material.specularTexId
            << material.normalTexId
            << material.heightTexId;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEMaterial& material)
    {
        in >> material.id
            >> material.uniformData
            >> material.objectColor
            >> material.atlasTexId
            >> material.diffuseTexId
            >> material.specularTexId
            >> material.normalTexId
            >> material.heightTexId;

        return in;
    }
};
