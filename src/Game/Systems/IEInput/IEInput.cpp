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
    inputContainer->addValue("Forward", new InputKey(0, Qt::Key_W));
    inputContainer->addValue("Backward", new InputKey(0, Qt::Key_S));
    inputContainer->addValue("Left", new InputKey(0, Qt::Key_A));
    inputContainer->addValue("Right", new InputKey(0, Qt::Key_D));
    inputContainer->addValue("Jump", new InputKey(0, Qt::Key_Space));
}
