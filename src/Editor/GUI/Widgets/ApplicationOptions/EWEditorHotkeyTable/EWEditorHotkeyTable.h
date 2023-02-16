#pragma once

#include "EWHotkeyTable.h"

class EWEditorHotkeyTable : public EWHotkeyTable
{

public:
    EWEditorHotkeyTable(InputContainer* inputContainer, QWidget* parent = nullptr);
    ~EWEditorHotkeyTable();

private:
    void setupTables(InputContainer* inputContainer);
};

