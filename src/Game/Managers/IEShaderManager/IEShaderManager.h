#pragma once

#include "IEResourceManager.h"
#include "Serializable.h"
#include "IEShader.h"

class GameStartEvent;

class IEShaderManager : public IEResourceManager<IEShader>, public Serializable
{
    Q_OBJECT

public:
    IEShaderManager();
    ~IEShaderManager();

    bool add(const unsigned long long key, std::unique_ptr<IEShader> value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

private:
    void buildAllShaders();

signals:
    void added(const unsigned long long key, const QString& path);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
