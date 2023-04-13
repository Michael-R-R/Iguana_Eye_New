#include "EMessageLogWindow.h"

EMessageLogWindow::EMessageLogWindow(QWidget* parent) :
    EWindow("Message Log", parent),
    messageLog(new EWMessageLog(this))
{
    this->setWidget(messageLog);
}

EMessageLogWindow::~EMessageLogWindow()
{

}

void EMessageLogWindow::startup()
{

}
