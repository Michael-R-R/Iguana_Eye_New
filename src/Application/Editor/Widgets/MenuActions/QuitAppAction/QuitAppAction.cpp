#include "QuitAppAction.h"
#include <QApplication>

QuitAppAction::QuitAppAction(InputKey* shortcut, QObject* parent) :
    MenuAction("Quit", shortcut, parent)
{
    connect(this, &QAction::triggered, this, [this]()
    {
        QApplication::quit();
    });
}

QuitAppAction::~QuitAppAction()
{

}
