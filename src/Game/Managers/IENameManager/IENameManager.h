#pragma once

#include <QDataStream>
#include <tuple>

#include "IEObject.h"
#include "IEResourceContainer.h"

class IENameManager : public IEObject
{
    Q_OBJECT

    IEResourceContainer<QString> resourceContainer;

public:
    IENameManager(QObject* parent = nullptr);
    ~IENameManager();

    bool add(const unsigned long long key, QString* value);
    bool remove(const unsigned long long key);
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey);
    bool doesExist(const unsigned long long key) const;
    bool doesExist(const QString* value) const;
    std::tuple<unsigned long long, QString> hashString(const QString& value) const;

    const QString* getValue(const unsigned long long key) const;
    const QMap<unsigned long long, QString*>& getResources() const;
    const IEResourceContainer<QString>& getResourceContainer() const;

    void setResourceContainer(const IEResourceContainer<QString> val);

signals:
    void added(const unsigned long long key, const QString* value);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);
};

QDataStream& operator<<(QDataStream& out, const IENameManager& manager);
QDataStream& operator>>(QDataStream& in, IENameManager& manager);
