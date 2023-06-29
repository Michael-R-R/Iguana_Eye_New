#include "InputCapture.h"

InputCapture::InputCapture(QWidget* parent) :
    QWidget(parent),
    capturedInput(),
    lastKey(), currKey(),
    lastMod(Qt::NoModifier),
    cursorPos()
{
    parent->setFocusPolicy(Qt::StrongFocus);
    parent->setFocus();
    parent->setMouseTracking(true);
    parent->installEventFilter(this);
}

InputCapture::~InputCapture()
{

}

void InputCapture::clear()
{
    currKey = InputKey();
    cursorPos = QVector2D();
    capturedInput.clear();
}

bool InputCapture::checkStatus(const InputKey& key)
{
    return capturedInput[key];
}

bool InputCapture::eventFilter(QObject* watched, QEvent* event)
{
    checkEvent(event);

    return QObject::eventFilter(watched, event);
}

void InputCapture::mousePressEvent(QMouseEvent* event)
{
    if(!event) { return; }

    int mods = event->modifiers();
    int key = event->button();
    if(lastMod != mods) { capturedInput.clear(); }

    lastMod = mods;
    lastKey = currKey;
    currKey = InputKey(mods, key);
    capturedInput[currKey] = true;

    emit inputPressed(currKey);
}

void InputCapture::mouseReleaseEvent(QMouseEvent* event)
{
    if(!event) { return; }

    int mods = event->modifiers();
    int key = event->button();
    if(lastMod != mods) { capturedInput.clear(); }

    lastMod = mods;
    lastKey = currKey;
    currKey = InputKey(mods, key);
    capturedInput[currKey] = false;

    emit inputReleased(currKey);
}

void InputCapture::mouseMoveEvent(QMouseEvent* event)
{
    if(!event) { return; }

    cursorPos = QVector2D(event->pos());
}

void InputCapture::wheelEvent(QWheelEvent* event)
{
    if(!event) { return; }

    emit wheelDeltaChanged(event->angleDelta());
}

void InputCapture::keyPressEvent(QKeyEvent* event)
{
    if(!event) { return; }
    if(event->isAutoRepeat()) { return; }

    int mods = event->modifiers();
    int key = event->key();
    if(lastMod != mods) { capturedInput.clear(); }

    lastMod = mods;
    lastKey = currKey;
    currKey = InputKey(mods, key);
    capturedInput[currKey] = true;

    emit inputPressed(currKey);
}

void InputCapture::keyReleaseEvent(QKeyEvent* event)
{
    if(!event) { return; }
    if(event->isAutoRepeat()) { return; }

    int mods = event->modifiers();
    int key = event->key();
    if(lastMod != mods) { capturedInput.clear(); }

    lastMod = mods;
    lastKey = currKey;
    currKey = InputKey(mods, key);
    capturedInput[currKey] = false;

    emit inputReleased(currKey);
}

void InputCapture::focusOutEvent(QFocusEvent* event)
{
    if(!event) { return; }
    clear();
}

void InputCapture::checkEvent(QEvent* event)
{
    switch(event->type())
    {
    case QEvent::MouseButtonPress: { mousePressEvent(static_cast<QMouseEvent*>(event)); break; }
    case QEvent::MouseButtonRelease: { mouseReleaseEvent(static_cast<QMouseEvent*>(event)); break; }
    case QEvent::MouseMove: { mouseMoveEvent(static_cast<QMouseEvent*>(event)); break; }
    case QEvent::Wheel: { wheelEvent(static_cast<QWheelEvent*>(event)); break; }
    case QEvent::KeyPress: { keyPressEvent(static_cast<QKeyEvent*>(event)); break; }
    case QEvent::KeyRelease: { keyReleaseEvent(static_cast<QKeyEvent*>(event)); break; }
    case QEvent::FocusOut: { focusOutEvent(static_cast<QFocusEvent*>(event)); break; }
    }
}
