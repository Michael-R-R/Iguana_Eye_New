#pragma once

#include "IEObject.h"
#include "InputContainer.h"
#include "InputCapture.h"

class QWidget;

class GLInput : public IEObject
{
    Q_OBJECT

    InputContainer* inputContainer;
    InputCapture* inputCapture;

public:
    GLInput(QWidget* hostWidget, QObject* parent = nullptr);
    ~GLInput();

    bool isPressed(const InputKey& key);
    bool isPressed(const char* keyName);

    InputContainer* getInputContainer() const { return inputContainer; }
    InputCapture* getInputCapture() const { return inputCapture; }
};
