#pragma once

#include "InputContainer.h"

class EInput
{
    InputContainer inputContainer;

public:
    EInput();
    ~EInput();

    void startup();

    InputContainer& getInputContainer() { return inputContainer; }
};

