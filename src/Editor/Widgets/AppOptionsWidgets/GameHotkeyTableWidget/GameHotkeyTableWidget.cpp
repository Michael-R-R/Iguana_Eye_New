#include "GameHotkeyTableWidget.h"

GameHotkeyTableWidget::GameHotkeyTableWidget(InputContainer* inputContainer, QWidget* parent) :
    HotkeyTableWidget(parent)
{
    setupTables(inputContainer);
}

GameHotkeyTableWidget::~GameHotkeyTableWidget()
{

}

void GameHotkeyTableWidget::setupTables(InputContainer* inputContainer)
{
    QMap<QString, InputKey*> movementKeys;
    addKeyToMap(inputContainer, "Forward", movementKeys);
    addKeyToMap(inputContainer, "Backward", movementKeys);
    addKeyToMap(inputContainer, "Left", movementKeys);
    addKeyToMap(inputContainer, "Right", movementKeys);
    addKeyToMap(inputContainer, "Jump", movementKeys);
    this->addTable("Movement", createTable(inputContainer, movementKeys));
}
