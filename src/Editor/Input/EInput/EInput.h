#pragma once

#include "BaseInput.h"
#include "InputContainer.h"

class EInput : public BaseInput
{

public:
    EInput(QObject *parent = nullptr);
    ~EInput();

protected:
    void setupInputContainer() override;

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

