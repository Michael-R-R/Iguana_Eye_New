#pragma once

#include "IEResourceManager.h"
#include "IERenderable.h"

class IERenderableManager : public IEResourceManager<IERenderable>
{
    Q_OBJECT

public:
    IERenderableManager();
    ~IERenderableManager();

    bool add(const unsigned long long key, QSharedPointer<IERenderable> value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;
    bool doesExist(const unsigned long long meshId,
                   const unsigned long long materialId,
                   const unsigned long long shaderId);

private:
    void buildAll();

signals:
    void added(const unsigned long long key, const QString& path);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
