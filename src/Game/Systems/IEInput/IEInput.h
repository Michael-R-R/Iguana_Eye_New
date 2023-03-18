#pragma once

#include "BaseInput.h"
#include "InputContainer.h"
#include "InputCapture.h"

class QWidget;

class IEInput : public BaseInput
{
    std::unique_ptr<InputCapture> inputCapture;

public:
    IEInput(QWidget* hostWidget);
    ~IEInput();

    bool isPressed(const InputKey& key);
    bool isPressed(const char* keyName);
    QPoint cursorPos() const;
    QPoint wheelDelta() const;

protected:
    void setupInputContainer() override;

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
