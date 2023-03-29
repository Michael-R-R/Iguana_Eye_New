#include "EWEditorHotkeyTable.h"
#include "BaseInput.h"
#include "InputKey.h"

EWEditorHotkeyTable::EWEditorHotkeyTable(BaseInput* input, QWidget* parent) :
    EWHotkeyTable(parent)
{
    setupTables(input);
}

EWEditorHotkeyTable::~EWEditorHotkeyTable()
{

}

void EWEditorHotkeyTable::setupTables(BaseInput* input)
{
    QMap<QString, InputKey*> applicationKeys;
    applicationKeys["New File"] = &input->getConfigKey("New File");
    applicationKeys["Open File"] = &input->getConfigKey("Open File");
    applicationKeys["Save File"] = &input->getConfigKey("Save File");
    applicationKeys["Save File As"] = &input->getConfigKey("Save File As");
    applicationKeys["Toggle Ui"] = &input->getConfigKey("Toggle Ui");
    applicationKeys["Quit"] = &input->getConfigKey("Quit");
    this->addTable("Application", this->createTable(input, applicationKeys));

    QMap<QString, InputKey*> gameKeys;
    gameKeys["Toggle Rendering"] = &input->getConfigKey("Toggle Rendering");
    gameKeys["Toggle Updating"] = &input->getConfigKey("Toggle Updating");
    this->addTable("Game", this->createTable(input, gameKeys));

    QMap<QString, InputKey*> windowKeys;
    windowKeys["Options"] = &input->getConfigKey("Options");
    windowKeys["File Explorer"] = &input->getConfigKey("File Explorer");
    windowKeys["GLSL Editor"] = &input->getConfigKey("GLSL Editor");
    windowKeys["Message Log"] = &input->getConfigKey("Message Log");
    this->addTable("Window", this->createTable(input, windowKeys));
}
