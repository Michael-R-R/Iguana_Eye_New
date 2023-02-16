#include "EWEditorHotkeyTable.h"

EWEditorHotkeyTable::EWEditorHotkeyTable(InputContainer* inputContainer, QWidget* parent) :
    EWHotkeyTable(parent)
{
    setupTables(inputContainer);
}

EWEditorHotkeyTable::~EWEditorHotkeyTable()
{

}

void EWEditorHotkeyTable::setupTables(InputContainer* inputContainer)
{
    QMap<QString, InputKey*> applicationKeys;
    addKeyToMap(inputContainer, "New File", applicationKeys);
    addKeyToMap(inputContainer, "Open File", applicationKeys);
    addKeyToMap(inputContainer, "Save File", applicationKeys);
    addKeyToMap(inputContainer, "Save File As", applicationKeys);
    addKeyToMap(inputContainer, "Options", applicationKeys);
    addKeyToMap(inputContainer, "Toggle Ui", applicationKeys);
    addKeyToMap(inputContainer, "Quit", applicationKeys);
    this->addTable("Application", createTable(inputContainer, applicationKeys));

    QMap<QString, InputKey*> gameKeys;
    addKeyToMap(inputContainer, "Toggle Rendering", gameKeys);
    addKeyToMap(inputContainer, "Toggle Updating", gameKeys);
    this->addTable("Game", createTable(inputContainer, gameKeys));
}
