#pragma once

#include <QObject>

#include "InputContainer.h"

class EditorInput : public QObject
{
    InputContainer* inputContainer;

public:
    EditorInput(QObject *parent = nullptr);
    ~EditorInput();

    void setup();

    InputContainer* getInputContainer() { return inputContainer; }
};

