#pragma once

#include "EWHotkeyTable.h"

class BaseInput;

class EWEditorHotkeyTable : public EWHotkeyTable
{

public:
    EWEditorHotkeyTable(BaseInput* input, QWidget* parent = nullptr);
    ~EWEditorHotkeyTable();

private:
    void setupTables(BaseInput* input);
};

