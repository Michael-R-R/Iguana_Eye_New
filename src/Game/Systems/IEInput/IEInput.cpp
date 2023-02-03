#include "IEInput.h"

IEInput::IEInput(QWidget* hostWidget, QObject* parent) :
    IEObject(parent),
    inputContainer(new InputContainer(this)),
    inputCapture(new InputCapture(hostWidget))
{
    setupInputContainer();
}

IEInput::~IEInput()
{
    delete inputCapture;
}

bool IEInput::isPressed(const InputKey& key)
{
    return inputCapture->checkStatus(key);
}

bool IEInput::isPressed(const char* keyName)
{
    const InputKey* key = inputContainer->fetchValue(keyName);
    return inputCapture->checkStatus(*key);
}

void IEInput::setupInputContainer()
{
    inputContainer->addValue("Forward", InputKey(0, Qt::Key_W));
    inputContainer->addValue("Backward", InputKey(0, Qt::Key_S));
    inputContainer->addValue("Left", InputKey(0, Qt::Key_A));
    inputContainer->addValue("Right", InputKey(0, Qt::Key_D));
    inputContainer->addValue("Jump", InputKey(0, Qt::Key_Space));
}

QDataStream& operator<<(QDataStream& out, const IEInput& input)
{
    out << *input.getInputContainer();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEInput& input)
{
    auto inputContainer = input.getInputContainer();

    in >> *inputContainer;

    input.setInputContainer(inputContainer);

    return in;
}
