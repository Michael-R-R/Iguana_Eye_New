#include "GLInput.h"

GLInput::GLInput(QWidget* hostWidget, QObject* parent) :
    IEObject(parent),
    inputContainer(new InputContainer(this)),
    inputCapture(new InputCapture(hostWidget))
{

}

GLInput::~GLInput()
{
    delete inputCapture;
}

bool GLInput::isPressed(const InputKey& key)
{
    return inputCapture->checkStatus(key);
}

bool GLInput::isPressed(const char* keyName)
{
    const InputKey* key = inputContainer->fetchValue(keyName);
    return inputCapture->checkStatus(*key);
}
