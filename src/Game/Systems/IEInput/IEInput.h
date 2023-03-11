#pragma once

#include "IEObject.h"
#include "Serializable.h"
#include "InputContainer.h"
#include "InputCapture.h"

class QWidget;

class IEInput : public IEObject, public Serializable
{
    Q_OBJECT

    std::unique_ptr<InputContainer> inputContainer;
    std::unique_ptr<InputCapture> inputCapture;

public:
    IEInput(QWidget* hostWidget);
    ~IEInput();

    bool isPressed(const InputKey& key);
    bool isPressed(const QString& keyName);

    InputContainer& getInputContainer() const { return *inputContainer; }
    InputCapture& getInputCapture() const { return *inputCapture; }

private:
    void setupInputContainer();

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
