#pragma once

#include "HotkeyTableWidget.h"

class EditorHotkeyTableWidget : public HotkeyTableWidget
{

public:
    EditorHotkeyTableWidget(InputContainer* inputContainer, QWidget* parent = nullptr);
    ~EditorHotkeyTableWidget();

private:
    void setupTables(InputContainer* inputContainer);
};

