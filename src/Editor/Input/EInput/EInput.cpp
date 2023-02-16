#include "EInput.h"

EInput::EInput(QObject* parent) :
    QObject(parent),
    inputContainer(new InputContainer(this))
{

}

EInput::~EInput()
{

}

void EInput::setup()
{
    inputContainer->addValue("New File", new InputKey(Qt::CTRL, Qt::Key_N));
    inputContainer->addValue("Open File", new InputKey(Qt::CTRL, Qt::Key_O));
    inputContainer->addValue("Save File", new InputKey(Qt::CTRL, Qt::Key_S));
    inputContainer->addValue("Save File As", new InputKey(Qt::CTRL | Qt::SHIFT, Qt::Key_S));
    inputContainer->addValue("Options", new InputKey(Qt::CTRL | Qt::ALT, Qt::Key_O));
    inputContainer->addValue("Quit", new InputKey(Qt::CTRL | Qt::ALT, Qt::Key_F4));
    inputContainer->addValue("Toggle Ui", new InputKey(0, Qt::Key_Tab));
    inputContainer->addValue("Toggle Rendering", new InputKey(Qt::ALT, Qt::Key_R));
    inputContainer->addValue("Toggle Updating", new InputKey(Qt::ALT, Qt::Key_U));
}
