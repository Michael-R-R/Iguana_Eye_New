#include "StatusBar.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "IETime.h"

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
    auto& time = event.getGame()->getIETime();

    connect(&time, &IETime::message, this, [this](const QString msg) { this->showMessage(msg); });
}
