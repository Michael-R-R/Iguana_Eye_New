#include "Window.h"

Window::Window(QString title, QWidget* parent) :
    QDockWidget(title, parent),
    isActive(false)
{
    this->setAttribute(Qt::WA_QuitOnClose, false);
    this->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->hide();
}

Window::~Window()
{

}

void Window::toggleVisibilty(bool status)
{
    if(status) { this->show(); }
    else { this->hide(); }
}

void Window::setStyleByString(const QString& style)
{
    this->setStyleSheet(style);
}

void Window::setStyleByFile(const QString& path)
{
    // TODO implement, once File util is added
}

void Window::showEvent(QShowEvent* event)
{
    QDockWidget::showEvent(event);
    isActive = true;
}

void Window::closeEvent(QCloseEvent* event)
{
    QDockWidget::closeEvent(event);
    isActive = false;
}
