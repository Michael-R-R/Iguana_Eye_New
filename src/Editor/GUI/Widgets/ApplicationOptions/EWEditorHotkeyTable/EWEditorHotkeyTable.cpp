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
    applicationKeys["New File"] = inputContainer->fetchValue("New File");
    applicationKeys["Open File"] = inputContainer->fetchValue("Open File");
    applicationKeys["Save File"] = inputContainer->fetchValue("Save File");
    applicationKeys["Save File As"] = inputContainer->fetchValue("Save File As");
    applicationKeys["Options"] = inputContainer->fetchValue("Options");
    applicationKeys["Toggle Ui"] = inputContainer->fetchValue("Toggle Ui");
    applicationKeys["Quit"] = inputContainer->fetchValue("Quit");
    this->addTable("Application", this->createTable(inputContainer, applicationKeys));

    QMap<QString, InputKey*> gameKeys;
    gameKeys["Toggle Rendering"] = inputContainer->fetchValue("Toggle Rendering");
    gameKeys["Toggle Updating"] = inputContainer->fetchValue("Toggle Updating");
    this->addTable("Game", this->createTable(inputContainer, gameKeys));
}
