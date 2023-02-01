#pragma once

#include "HotkeyTableWidget.h"

class GameHotkeyTableWidget : public HotkeyTableWidget
{
public:
    GameHotkeyTableWidget(InputContainer* inputContainer, QWidget* parent = nullptr);
    ~GameHotkeyTableWidget();

private:
    void setupTables(InputContainer* inputContainer);
};

