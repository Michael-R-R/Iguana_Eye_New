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
    movementKeys["Forward"] = inputContainer->fetchValue("Forward");
    movementKeys["Backward"] = inputContainer->fetchValue("Backward");
    movementKeys["Left"] = inputContainer->fetchValue("Left");
    movementKeys["Right"] = inputContainer->fetchValue("Right");
    movementKeys["Jump"] = inputContainer->fetchValue("Jump");
    this->addTable("Movement", this->createTable(inputContainer, movementKeys));
}
