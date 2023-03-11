#include "EWEditorHotkeyTable.h"

EWEditorHotkeyTable::EWEditorHotkeyTable(InputContainer& inputContainer, QWidget* parent) :
    EWHotkeyTable(parent)
{
    setupTables(inputContainer);
}

EWEditorHotkeyTable::~EWEditorHotkeyTable()
{

}

void EWEditorHotkeyTable::setupTables(InputContainer& inputContainer)
{
    QMap<QString, InputKey*> applicationKeys;
    applicationKeys["New File"] = &inputContainer.getValue("New File");
    applicationKeys["Open File"] = &inputContainer.getValue("Open File");
    applicationKeys["Save File"] = &inputContainer.getValue("Save File");
    applicationKeys["Save File As"] = &inputContainer.getValue("Save File As");
    applicationKeys["Toggle Ui"] = &inputContainer.getValue("Toggle Ui");
    applicationKeys["Quit"] = &inputContainer.getValue("Quit");
    this->addTable("Application", this->createTable(inputContainer, applicationKeys));

    QMap<QString, InputKey*> gameKeys;
    gameKeys["Toggle Rendering"] = &inputContainer.getValue("Toggle Rendering");
    gameKeys["Toggle Updating"] = &inputContainer.getValue("Toggle Updating");
    this->addTable("Game", this->createTable(inputContainer, gameKeys));

    QMap<QString, InputKey*> windowKeys;
    windowKeys["Options"] = &inputContainer.getValue("Options");
    windowKeys["File Explorer"] = &inputContainer.getValue("File Explorer");
    windowKeys["GLSL Editor"] = &inputContainer.getValue("GLSL Editor");
    this->addTable("Window", this->createTable(inputContainer, windowKeys));
}
