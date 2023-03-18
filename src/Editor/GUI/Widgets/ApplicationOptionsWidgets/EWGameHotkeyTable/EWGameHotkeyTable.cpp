#include "EWGameHotkeyTable.h"
#include "BaseInput.h"
#include "InputKey.h"

EWGameHotkeyTable::EWGameHotkeyTable(BaseInput* input, QWidget* parent) :
    EWHotkeyTable(parent)
{
    setupTables(input);
}

EWGameHotkeyTable::~EWGameHotkeyTable()
{

}

void EWGameHotkeyTable::setupTables(BaseInput* input)
{
    QMap<QString, InputKey*> movementKeys;
    movementKeys["Forward"] = &input->getConfigKey("Forward");
    movementKeys["Backward"] = &input->getConfigKey("Backward");
    movementKeys["Left"] = &input->getConfigKey("Left");
    movementKeys["Right"] = &input->getConfigKey("Right");
    movementKeys["Up"] = &input->getConfigKey("Up");
    movementKeys["Down"] = &input->getConfigKey("Down");
    movementKeys["Jump"] = &input->getConfigKey("Jump");
    this->addTable("Movement", this->createTable(input, movementKeys));
}
