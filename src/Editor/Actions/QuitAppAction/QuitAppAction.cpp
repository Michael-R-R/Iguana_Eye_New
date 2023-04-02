#include "QuitAppAction.h"
#include <QApplication>

QuitAppAction::QuitAppAction(InputKey& shortcut, QObject* parent) :
    BaseAction("Quit", shortcut, parent)
{
    connect(this, &QAction::triggered, this, [this]()
    {
        QApplication::quit();
    });
}

QuitAppAction::~QuitAppAction()
{

}
