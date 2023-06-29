#pragma once

#include "IEGameSystem.h"
#include "BaseInput.h"
#include "InputContainer.h"
#include "InputCapture.h"

class IEInput : public IEGameSystem, public BaseInput
{
    InputCapture* inputCapture;

public:
    IEInput(QObject* parent = nullptr);
    virtual ~IEInput();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void onDeserialize(IEGame& game) override;

    bool isPressed(const InputKey& key);
    bool isPressed(const char* keyName);
    const QVector2D& cursorPos() const;

    InputCapture* getInputCapture() const { return inputCapture; }

protected:
    void setupInputContainer() override;

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
