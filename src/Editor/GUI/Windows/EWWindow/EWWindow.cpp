#include "EWWindow.h"
#include "IEFile.h"

EWWindow::EWWindow(QString title, QWidget* parent) :
    QDockWidget(title, parent),
    isActive(false)
{
    this->setAttribute(Qt::WA_QuitOnClose, false);
    this->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->hide();
}

EWWindow::~EWWindow()
{

}

void EWWindow::toggleVisibilty(bool status)
{
    if(status) { this->show(); }
    else { this->hide(); }
}

void EWWindow::setStyleByString(const QString& style)
{
    this->setStyleSheet(style);
}

void EWWindow::setStyleByFile(const QString& path)
{
    QString style = "";
    if(!IEFile::read(path, &style))
        return;

    this->setStyleSheet(style);
}

void EWWindow::showEvent(QShowEvent* event)
{
    QDockWidget::showEvent(event);
    isActive = true;
}

void EWWindow::closeEvent(QCloseEvent* event)
{
    QDockWidget::closeEvent(event);
    isActive = false;
}
