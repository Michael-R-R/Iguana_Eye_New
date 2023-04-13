#include "EInput.h"

EInput::EInput(QObject* parent) :
    QObject(parent)
{

}

EInput::~EInput()
{

}

void EInput::startup()
{
    setupInputContainer();
}

void EInput::shutdown()
{
    inputContainer.clear();
}

void EInput::setupInputContainer()
{
    inputContainer.addValue("New File", InputKey(Qt::CTRL, Qt::Key_N));
    inputContainer.addValue("Open File", InputKey(Qt::CTRL, Qt::Key_O));
    inputContainer.addValue("Save File", InputKey(Qt::CTRL, Qt::Key_S));
    inputContainer.addValue("Save File As", InputKey(Qt::CTRL | Qt::SHIFT, Qt::Key_S));
    inputContainer.addValue("Options", InputKey(Qt::CTRL | Qt::ALT, Qt::Key_O));
    inputContainer.addValue("Quit", InputKey(Qt::CTRL | Qt::ALT, Qt::Key_F4));
    inputContainer.addValue("Toggle Ui", InputKey(0, Qt::Key_Tab));
    inputContainer.addValue("Toggle Play", InputKey(Qt::ALT, Qt::Key_P));
    inputContainer.addValue("Toggle Stop", InputKey(Qt::ALT, Qt::Key_S));
    inputContainer.addValue("File Explorer", InputKey(Qt::CTRL | Qt::ALT, Qt::Key_F));
    inputContainer.addValue("GLSL Editor", InputKey(Qt::CTRL | Qt::ALT, Qt::Key_G));
    inputContainer.addValue("Message Log", InputKey(Qt::CTRL | Qt::ALT, Qt::Key_L));
}
