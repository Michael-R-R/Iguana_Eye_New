#pragma once

#include <QObject>

#include "InputContainer.h"

class EInput : public QObject
{
    std::unique_ptr<InputContainer> inputContainer;

public:
    EInput(QObject *parent = nullptr);
    ~EInput();

    void startup();

    InputContainer& getInputContainer() const { return *inputContainer; }
};

