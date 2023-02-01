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

void StatusBar::setupIEObjectConnections(const AppStartEvent& event)
{
    auto time = event.game()->getTime();

    connect(time, &IETime::message, this, [this](const QString msg) { this->showMessage(msg); });
}
