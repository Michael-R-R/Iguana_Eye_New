#pragma once

#include "EWHotkeyTable.h"

class EWGameHotkeyTable : public EWHotkeyTable
{

public:
    EWGameHotkeyTable(InputContainer* inputContainer, QWidget* parent = nullptr);
    ~EWGameHotkeyTable();

private:
    void setupTables(InputContainer* inputContainer);
};

