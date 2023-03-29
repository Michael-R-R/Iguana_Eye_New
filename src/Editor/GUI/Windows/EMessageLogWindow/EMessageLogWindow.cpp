#include "EMessageLogWindow.h"
#include "AppStartEvent.h"

EMessageLogWindow::EMessageLogWindow(QWidget* parent) :
    EWindow("Message Log", parent),
    messageLog(new EWMessageLog(this))
{
    this->setWidget(messageLog);
}

EMessageLogWindow::~EMessageLogWindow()
{

}

void EMessageLogWindow::startup(const AppStartEvent&)
{
    // TODO test
    messageLog->insertMessage("Normal message", IEObject::MessageType::Normal);
    messageLog->insertMessage("Error message", IEObject::MessageType::Error);
}
