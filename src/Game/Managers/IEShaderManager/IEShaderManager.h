#pragma once

#include <QDataStream>

#include "IEManager.h"
#include "IEShader.h"

class IEShaderManager : public IEManager<IEShader>
{
    Q_OBJECT

public:
    IEShaderManager(QObject* parent = nullptr);
    ~IEShaderManager();

    bool add(const unsigned long long key, IEShader* value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

signals:
    void added(const unsigned long long key);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);
};

QDataStream& operator<<(QDataStream& out, const IEShaderManager& manager);
QDataStream& operator>>(QDataStream& in, IEShaderManager& manager);
