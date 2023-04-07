#pragma once

#include <QObject>

#include "BaseInput.h"
#include "InputContainer.h"

class EInput : public QObject, public BaseInput
{

public:
    EInput(QObject *parent = nullptr);
    ~EInput();

protected:
    void setupInputContainer() override;

};

