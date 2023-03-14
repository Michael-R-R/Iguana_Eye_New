#include "IEInput.h"

IEInput::IEInput(QWidget* hostWidget) :
    IEObject(),
    inputContainer(std::make_unique<InputContainer>()),
    inputCapture(std::make_unique<InputCapture>(hostWidget))
{
    setupInputContainer();
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
    const InputKey& key = inputContainer->getValue(keyName);

    return inputCapture->checkStatus(key);
}

void IEInput::setupInputContainer()
{
    inputContainer->addValue("Forward", InputKey(0, Qt::Key_W));
    inputContainer->addValue("Backward", InputKey(0, Qt::Key_S));
    inputContainer->addValue("Left", InputKey(0, Qt::Key_A));
    inputContainer->addValue("Right", InputKey(0, Qt::Key_D));
    inputContainer->addValue("Jump", InputKey(0, Qt::Key_Space));
}

QDataStream& IEInput::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& input = static_cast<const IEInput&>(obj);

    out << *input.inputContainer;

    return out;
}

QDataStream& IEInput::deserialize(QDataStream& in, Serializable& obj)
{
    auto& input = static_cast<IEInput&>(obj);

    in >> *input.inputContainer;

    return in;
}
