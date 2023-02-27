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
    bool isEdited;

public:
    IEMaterial();
    IEMaterial(const QString& path, const unsigned long long id);
    IEMaterial(const IEMaterial& other);
    ~IEMaterial();

    bool operator==(const IEMaterial& other) { return IEResource::operator==(other); }
    bool operator!=(const IEMaterial& other) { return IEResource::operator!=(other); }
    bool operator<(const IEMaterial& other) { return IEResource::operator<(other); }
    bool operator>(const IEMaterial& other) { return IEResource::operator>(other); }

    void bindUniformData(IEShader* shader) const;

    QColor getObjectColor() const { return objectColor; }
    unsigned long long getAtlasTexId() const { return atlasTexId; }
    unsigned long long getDiffuseTexId() const { return diffuseTexId; }
    unsigned long long getSpecularTexId() const { return specularTexId; }
    unsigned long long getNormalTexId() const { return normalTexId; }
    unsigned long long getHeightTexId() const { return heightTexId; }
    bool getIsEdited() const { return isEdited; }

    void setUniformData(const IEUniform& val) { uniformData = val; }
    void setObjectColor(const QColor val) { objectColor = val; }
    void setAtlasTexId(const unsigned long long val) { atlasTexId = val; }
    void setDiffuseTexId(const unsigned long long val) { diffuseTexId = val; }
    void setSpecularTexId(const unsigned long long val) { specularTexId = val; }
    void setNormalTexId(const unsigned long long val) { normalTexId = val; }
    void setHeightTexId(const unsigned long long val) { heightTexId = val; }
    void setIsEdited(const bool val) { isEdited = val; }

    friend QDataStream& operator<<(QDataStream& out, const IEMaterial& material)
    {
        out << material.filePath
            << material.id
            << material.type
            << material.uniformData
            << material.objectColor
            << material.atlasTexId
            << material.diffuseTexId
            << material.specularTexId
            << material.normalTexId
            << material.heightTexId
            << material.isEdited;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEMaterial& material)
    {
        in >> material.filePath
           >> material.id
           >> material.type
           >> material.uniformData
           >> material.objectColor
           >> material.atlasTexId
           >> material.diffuseTexId
           >> material.specularTexId
           >> material.normalTexId
           >> material.heightTexId
           >> material.isEdited;

        return in;
    }
};
