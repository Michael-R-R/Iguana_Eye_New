#pragma once

#include "IEObject.h"
#include "Serializable.h"
#include "InputContainer.h"

class BaseInput : public IEObject, public Serializable
{
protected:
    InputContainer inputContainer;

public:
    BaseInput(QObject* parent = nullptr);
    ~BaseInput();

    bool updateConfigKey(const QString& key, const int modVal, const int keyVal);
    QString getKeyName(const int mod, const int key) const;
    InputKey& getConfigKey(const char* key);
    bool doesExist(const int mod, const int key) const;

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;

protected:
    virtual void setupInputContainer() = 0;
};

