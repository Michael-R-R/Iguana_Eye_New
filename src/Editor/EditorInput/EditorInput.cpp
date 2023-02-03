#include "EditorInput.h"

EditorInput::EditorInput(QObject* parent) :
    QObject(parent),
    inputContainer(new InputContainer(this))
{

}

EditorInput::~EditorInput()
{

}

void EditorInput::setup()
{
    inputContainer->addValue("Open", InputKey(Qt::CTRL, Qt::Key_O));
    inputContainer->addValue("Save", InputKey(Qt::CTRL, Qt::Key_S));
    inputContainer->addValue("Save As", InputKey(Qt::CTRL | Qt::SHIFT, Qt::Key_S));
    inputContainer->addValue("Options", InputKey(Qt::CTRL | Qt::ALT, Qt::Key_O));
    inputContainer->addValue("Quit", InputKey(Qt::CTRL | Qt::ALT, Qt::Key_F4));
    inputContainer->addValue("Toggle Ui", InputKey(0, Qt::Key_Tab));
    inputContainer->addValue("Toggle Rendering", InputKey(Qt::ALT, Qt::Key_R));
    inputContainer->addValue("Toggle Updating", InputKey(Qt::ALT, Qt::Key_U));
}
