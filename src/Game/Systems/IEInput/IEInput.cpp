#include "IEInput.h"

IEInput::IEInput(QWidget* hostWidget) :
    BaseInput(),
    inputCapture(std::make_unique<InputCapture>(hostWidget))
{
    IEInput::setupInputContainer();
}

IEInput::~IEInput()
{

}

bool IEInput::isPressed(const InputKey& key)
{
    return inputCapture->checkStatus(key);
}

bool IEInput::isPressed(const char* keyName)
{
    const InputKey& key = inputContainer.getValue(keyName);

    return inputCapture->checkStatus(key);
}

QPoint IEInput::cursorPos() const
{
    return inputCapture->getCursorPos();
}

QPoint IEInput::wheelDelta() const
{
    return inputCapture->getWheelDelta();
}

void IEInput::setupInputContainer()
{
    inputContainer.addValue("Forward", InputKey(0, Qt::Key_W));
    inputContainer.addValue("Backward", InputKey(0, Qt::Key_S));
    inputContainer.addValue("Left", InputKey(0, Qt::Key_A));
    inputContainer.addValue("Right", InputKey(0, Qt::Key_D));
    inputContainer.addValue("Up", InputKey(0, Qt::Key_E));
    inputContainer.addValue("Down", InputKey(0, Qt::Key_Q));
    inputContainer.addValue("Jump", InputKey(0, Qt::Key_Space));
}

QDataStream& IEInput::serialize(QDataStream& out, const Serializable& obj) const
{
    return BaseInput::serialize(out, obj);
}

QDataStream& IEInput::deserialize(QDataStream& in, Serializable& obj)
{
    return BaseInput::deserialize(in, obj);
}
