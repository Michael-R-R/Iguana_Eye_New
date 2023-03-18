#include "EInput.h"

EInput::EInput(QObject* parent) :
    BaseInput(parent)
{
    EInput::setupInputContainer();
}

EInput::~EInput()
{

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
    inputContainer.addValue("Toggle Rendering", InputKey(Qt::ALT, Qt::Key_R));
    inputContainer.addValue("Toggle Updating", InputKey(Qt::ALT, Qt::Key_U));
    inputContainer.addValue("File Explorer", InputKey(Qt::CTRL | Qt::ALT, Qt::Key_F));
    inputContainer.addValue("GLSL Editor", InputKey(Qt::CTRL | Qt::ALT, Qt::Key_G));
}

QDataStream& EInput::serialize(QDataStream& out, const Serializable& obj) const
{
    return BaseInput::serialize(out, obj);
}

QDataStream& EInput::deserialize(QDataStream& in, Serializable& obj)
{
    return BaseInput::deserialize(in, obj);
}
