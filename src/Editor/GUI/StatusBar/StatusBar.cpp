#include "StatusBar.h"
#include "AppStartEvent.h"

StatusBar::StatusBar(QWidget* parent) :
    QStatusBar(parent)
{
    this->showMessage("Ready");
}

StatusBar::~StatusBar()
{

}

void StatusBar::setupIEObjectConnections(const AppStartEvent&)
{

}
