#pragma once

#include "InputContainer.h"

class BaseInput
{
protected:
    InputContainer inputContainer;

public:
    BaseInput();
    ~BaseInput();

    bool updateConfigKey(const QString& key, const int modVal, const int keyVal);
    QString getKeyName(const int mod, const int key) const;
    InputKey& getConfigKey(const char* key);
    bool doesExist(const int mod, const int key) const;

protected:
    virtual void setupInputContainer() = 0;
};

