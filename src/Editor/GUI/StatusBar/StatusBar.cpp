#include "StatusBar.h"

StatusBar::StatusBar(QWidget* parent) :
    QStatusBar(parent)
{
    this->showMessage("Ready");
}

StatusBar::~StatusBar()
{

}

void StatusBar::startup()
{

}
