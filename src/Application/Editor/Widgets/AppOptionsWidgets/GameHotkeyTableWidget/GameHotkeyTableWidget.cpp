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
    movementKeys["Forward"] = inputContainer->fetchValue("Forward");
    movementKeys["Backward"] = inputContainer->fetchValue("Backward");
    movementKeys["Left"] = inputContainer->fetchValue("Left");
    movementKeys["Right"] = inputContainer->fetchValue("Right");
    this->addTable("Movement", createTable(inputContainer, movementKeys));
}
