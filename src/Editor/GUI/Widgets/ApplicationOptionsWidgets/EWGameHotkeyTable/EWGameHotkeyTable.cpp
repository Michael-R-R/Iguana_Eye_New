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
    movementKeys["Forward"] = inputContainer->getValue("Forward");
    movementKeys["Backward"] = inputContainer->getValue("Backward");
    movementKeys["Left"] = inputContainer->getValue("Left");
    movementKeys["Right"] = inputContainer->getValue("Right");
    movementKeys["Jump"] = inputContainer->getValue("Jump");
    this->addTable("Movement", this->createTable(inputContainer, movementKeys));
}
