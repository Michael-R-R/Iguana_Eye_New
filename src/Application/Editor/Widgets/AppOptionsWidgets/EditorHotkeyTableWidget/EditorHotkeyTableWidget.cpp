#include "EditorHotkeyTableWidget.h"

EditorHotkeyTableWidget::EditorHotkeyTableWidget(InputContainer* inputContainer, QWidget* parent) :
    HotkeyTableWidget(parent)
{
    setupTables(inputContainer);
}

EditorHotkeyTableWidget::~EditorHotkeyTableWidget()
{

}

void EditorHotkeyTableWidget::setupTables(InputContainer* inputContainer)
{
    QMap<QString, InputKey*> applicationKeys;
    applicationKeys["Quit"] = inputContainer->fetchValue("Quit");
    this->addTable("Application", createTable(inputContainer, applicationKeys));

    QMap<QString, InputKey*> editorKeys;
    editorKeys["Options"] = inputContainer->fetchValue("Options");
    editorKeys["Toggle Ui"] = inputContainer->fetchValue("Toggle Ui");
    editorKeys["Toggle Rendering"] = inputContainer->fetchValue("Toggle Rendering");
    editorKeys["Toggle Updating"] = inputContainer->fetchValue("Toggle Updating");
    this->addTable("Editor", createTable(inputContainer, editorKeys));
}
