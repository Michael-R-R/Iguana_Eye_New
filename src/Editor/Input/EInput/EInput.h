#pragma once

#include <QObject>

#include "InputContainer.h"

class EInput : public QObject
{
    InputContainer* inputContainer;

public:
    EInput(QObject *parent = nullptr);
    ~EInput();

    void startup();

    InputContainer* getInputContainer() { return inputContainer; }
};

