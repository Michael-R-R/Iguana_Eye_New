#pragma once

#include "EWHotkeyTable.h"

class BaseInput;

class EWGameHotkeyTable : public EWHotkeyTable
{

public:
    EWGameHotkeyTable(BaseInput* input, QWidget* parent = nullptr);
    ~EWGameHotkeyTable();

private:
    void setupTables(BaseInput* input);
};

