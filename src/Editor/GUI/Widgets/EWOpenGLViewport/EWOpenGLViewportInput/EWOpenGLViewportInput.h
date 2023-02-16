#pragma once

#include "IEObject.h"
#include "InputContainer.h"
#include "InputCapture.h"

class QWidget;

class EWOpenGLViewportInput : public IEObject
{
    Q_OBJECT

    InputContainer* inputContainer;
    InputCapture* inputCapture;

public:
    EWOpenGLViewportInput(QWidget* hostWidget, QObject* parent = nullptr);
    ~EWOpenGLViewportInput();

    bool isPressed(const InputKey& key);
    bool isPressed(const char* keyName);

    InputContainer* getInputContainer() const { return inputContainer; }
    InputCapture* getInputCapture() const { return inputCapture; }
};
