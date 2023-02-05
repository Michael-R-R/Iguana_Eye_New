#pragma once

#include <QDataStream>
#include <tuple>

#include "IEManager.h"

class IENameManager : public IEManager<QString>
{
    Q_OBJECT

public:
    IENameManager(QObject* parent = nullptr);
    ~IENameManager();

    void startup() override;
    void shutdown() override;

    bool add(const unsigned long long key, QString* value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

    std::tuple<unsigned long long, QString> hashString(const QString& value) const;

signals:
    void added(const unsigned long long key);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);
};

QDataStream& operator<<(QDataStream& out, const IENameManager& manager);
QDataStream& operator>>(QDataStream& in, IENameManager& manager);
