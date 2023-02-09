#pragma once

#include <QDataStream>

#include "IEObject.h"
#include "InputContainer.h"
#include "InputCapture.h"

class QWidget;

class IEInput : public IEObject
{
    Q_OBJECT

    InputContainer* inputContainer;
    InputCapture* inputCapture;

public:
    IEInput(QWidget* hostWidget, QObject* parent = nullptr);
    ~IEInput();

    bool isPressed(const InputKey& key);
    bool isPressed(const char* keyName);

    InputContainer* getInputContainer() const { return inputContainer; }
    InputCapture* getInputCapture() const { return inputCapture; }

private:
    void setupInputContainer();

public:
    friend QDataStream& operator<<(QDataStream& out, const IEInput& input)
    {
        out << *input.inputContainer;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEInput& input)
    {
        in >> *input.inputContainer;
        return in;
    }
};
