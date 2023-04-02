#include "BaseAction.h"

BaseAction::BaseAction(QString title, InputKey& shortcut, QObject* parent) :
    QAction(title, parent)
{
    this->setShortcut(shortcut.getKeySequence());

    connect(&shortcut, &InputKey::updated, &shortcut, [this](const QKeySequence val)
    {
        this->setShortcut(val);
    });
}

BaseAction::~BaseAction()
{

}
