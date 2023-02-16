#include "EWGameHotkeyTable.h"

EWGameHotkeyTable::EWGameHotkeyTable(InputContainer* inputContainer, QWidget* parent) :
    EWHotkeyTable(parent)
{
    setupTables(inputContainer);
}

EWGameHotkeyTable::~EWGameHotkeyTable()
{

}

void EWGameHotkeyTable::setupTables(InputContainer* inputContainer)
{
    QMap<QString, InputKey*> movementKeys;
    addKeyToMap(inputContainer, "Forward", movementKeys);
    addKeyToMap(inputContainer, "Backward", movementKeys);
    addKeyToMap(inputContainer, "Left", movementKeys);
    addKeyToMap(inputContainer, "Right", movementKeys);
    addKeyToMap(inputContainer, "Jump", movementKeys);
    this->addTable("Movement", createTable(inputContainer, movementKeys));
}
