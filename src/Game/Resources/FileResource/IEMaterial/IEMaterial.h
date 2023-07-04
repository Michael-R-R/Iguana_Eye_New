#pragma once

#include <QHash>
#include <QVector>
#include <QVector4D>

#include "IEFileResource.h"
#include "IEEnum.h"

class IEShader;

class IEMaterial : public IEFileResource
{
protected:
    QHash<IEColorType, const char*> colorNames;
    QHash<IEColorType, QVector4D> colors;
    QHash<IETextureType, uint64_t> textureIDs;

    IEMaterial* parent;
    QVector<IEMaterial*> children;
    QVector<IEMaterial*> materials;

public:
    IEMaterial(QObject* parent = nullptr);
    IEMaterial(const QString& path, QObject* parent = nullptr);
    IEMaterial(const IEMaterial&) = delete;
    virtual ~IEMaterial();

    bool operator==(const IEMaterial& other) { return IEFileResource::operator==(other); }
    bool operator!=(const IEMaterial& other) { return IEFileResource::operator!=(other); }
    bool operator<(const IEMaterial& other) { return IEFileResource::operator<(other); }
    bool operator>(const IEMaterial& other) { return IEFileResource::operator>(other); }

    void bindColors(IEShader& shader);

    void setColor(IEColorType type, const QVector4D& val);
    void removeColor(IEColorType type);

    void setTextureID(IETextureType type, const uint64_t val);
    void removeTextureID(IETextureType type);

    const QHash<IEColorType, QVector4D>& getColors() const { return colors; }
    const QHash<IETextureType, uint64_t>& getTexIDs() const { return textureIDs; }
    IEMaterial* getParent() { return parent; }
    QVector<IEMaterial*>& getChildren() { return children; }
    QVector<IEMaterial*>& getMaterials() { return materials; }

    void setParent(IEMaterial* val) { parent = val; }

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;

private:
    void setup();
};
