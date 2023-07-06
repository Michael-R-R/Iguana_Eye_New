#include "IEInput.h"
#include "IEGame.h"

IEInput::IEInput(QObject* parent) :
    IESystem(parent),
    inputCapture(nullptr)
{

}

IEInput::~IEInput()
{

}

void IEInput::startup(IEGame& game)
{
    inputCapture = new InputCapture(&game);
    setupInputContainer();
}

void IEInput::shutdown(IEGame&)
{
    inputContainer.clear();

    delete inputCapture;
    inputCapture = nullptr;
}

void IEInput::onDeserialize(IEGame&)
{
    inputContainer.clear();
}

bool IEInput::isPressed(const InputKey& key)
{
    return inputCapture->checkStatus(key);
}

bool IEInput::isPressed(const char* keyName)
{
    const InputKey& key = inputContainer.getValue(keyName);

    return inputCapture->checkStatus(key);
}

const QVector2D& IEInput::cursorPos() const
{
    return inputCapture->getCursorPos();
}

void IEInput::setupInputContainer()
{
    inputContainer.addValue("Forward", InputKey(0, Qt::Key_W));
    inputContainer.addValue("Backward", InputKey(0, Qt::Key_S));
    inputContainer.addValue("Left", InputKey(0, Qt::Key_A));
    inputContainer.addValue("Right", InputKey(0, Qt::Key_D));
    inputContainer.addValue("Up", InputKey(0, Qt::Key_E));
    inputContainer.addValue("Down", InputKey(0, Qt::Key_Q));
    inputContainer.addValue("Jump", InputKey(0, Qt::Key_Space));
    inputContainer.addValue("Left Click", InputKey(0, Qt::LeftButton));
    inputContainer.addValue("Middle Click", InputKey(0, Qt::MiddleButton));
    inputContainer.addValue("Right Click", InputKey(0, Qt::RightButton));
}

QDataStream& IEInput::serialize(QDataStream& out, const IESerializable& obj) const
{
    const IEInput& input = static_cast<const IEInput&>(obj);

    out << input.inputContainer;

    return out;
}

QDataStream& IEInput::deserialize(QDataStream& in, IESerializable& obj)
{
    IEInput& input = static_cast<IEInput&>(obj);

    in >> input.inputContainer;

    return in;
}
