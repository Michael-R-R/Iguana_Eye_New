#include "EWOpenGLViewportInput.h"

EWOpenGLViewportInput::EWOpenGLViewportInput(QWidget* hostWidget, QObject* parent) :
    IEObject(parent),
    inputContainer(new InputContainer(this)),
    inputCapture(new InputCapture(hostWidget))
{

}

EWOpenGLViewportInput::~EWOpenGLViewportInput()
{
    delete inputCapture;
}

bool EWOpenGLViewportInput::isPressed(const InputKey& key)
{
    return inputCapture->checkStatus(key);
}

bool EWOpenGLViewportInput::isPressed(const char* keyName)
{
    const InputKey* key = inputContainer->fetchValue(keyName);
    return inputCapture->checkStatus(*key);
}
