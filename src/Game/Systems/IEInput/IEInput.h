#pragma once

#include "IEGameSystem.h"
#include "BaseInput.h"
#include "InputContainer.h"
#include "InputCapture.h"

class QWidget;

class IEInput : public IEGameSystem, public BaseInput
{
    IEInput();
    static IEInput mInstance;

    std::unique_ptr<InputCapture> inputCapture;

public:
    static IEInput& instance();
    ~IEInput();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void initalize(IEGame& game) override;
    void reset(IEGame& game) override;

    bool isPressed(const InputKey& key);
    bool isPressed(const char* keyName);
    const QVector2D& cursorPos() const;
    const QVector2D& wheelDelta() const;

protected:
    void setupInputContainer() override;

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
