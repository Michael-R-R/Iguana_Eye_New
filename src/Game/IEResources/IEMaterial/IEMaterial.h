#pragma once

#include <QDataStream>

#include "IEResource.h"

class IEMaterial : public IEResource
{
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

    unsigned long long getAtlasTexId() const { return atlasTexId; }
    unsigned long long getDiffuseTexId() const { return diffuseTexId; }
    unsigned long long getSpecularTexId() const { return specularTexId; }
    unsigned long long getNormalTexId() const { return normalTexId; }
    unsigned long long getHeightTexId() const { return heightTexId; }

    void setAtlasTexId(const unsigned long long val) { atlasTexId = val; }
    void setDiffuseTexId(const unsigned long long val) { diffuseTexId = val; }
    void setSpecularTexId(const unsigned long long val) { specularTexId = val; }
    void setNormalTexId(const unsigned long long val) { normalTexId = val; }
    void setHeightTexId(const unsigned long long val) { heightTexId = val; }
};

QDataStream& operator<<(QDataStream& out, const IEMaterial& material);
QDataStream& operator>>(QDataStream& in, IEMaterial& material);
