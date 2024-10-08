#include "EWCollapsingHeader.h"

EWCollapsingHeader::EWCollapsingHeader(QString title, QWidget* parent) :
    QWidget(parent),
    vLayout(new QVBoxLayout(this)),
    hLayout(new QHBoxLayout()),
    headerFrame(new QFrame(this)),
    headerButton(new QToolButton(this)),
    isOpen(true),
    widgetCollection()
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    vLayout->setContentsMargins(4, 4, 4, 4);
    vLayout->addLayout(hLayout);
    vLayout->addStretch(1);

    hLayout->addWidget(headerButton);
    hLayout->addWidget(headerFrame);

    setupHeaderFrame();
    setupHeaderButton(title);
}

EWCollapsingHeader::~EWCollapsingHeader()
{

}

bool EWCollapsingHeader::appendWidget(const QString title, QWidget* widget)
{
    if(doesExist(title)) { return false; }

    widgetCollection[title] = widget;
    vLayout->insertWidget(vLayout->count() - 1, widget);

    return true;
}

bool EWCollapsingHeader::removeWidget(const QString& title)
{
    if(!doesExist(title)) { return false; }

    auto temp = widgetCollection[title];
    widgetCollection.remove(title);
    vLayout->removeWidget(temp);
    delete temp;

    return true;
}

bool EWCollapsingHeader::doesExist(const QString& title)
{
    return (widgetCollection.find(title) != widgetCollection.end());
}

QWidget* EWCollapsingHeader::getWidget(const QString& title)
{
    if(!doesExist(title)) { return nullptr; }
    return widgetCollection[title];
}

void EWCollapsingHeader::setupHeaderFrame()
{
    headerFrame->setFrameShape(QFrame::HLine);
    headerFrame->setFrameShadow(QFrame::Sunken);
    headerFrame->setFixedHeight(2);
}

void EWCollapsingHeader::setupHeaderButton(const QString& title)
{
    headerButton->setText(title);
    headerButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    headerButton->setArrowType(Qt::ArrowType::DownArrow);

    connect(headerButton, &QToolButton::clicked, headerButton, [this]()
    {
        if(isOpen)
        {
            headerButton->setArrowType(Qt::ArrowType::RightArrow);
            foreach(auto item, widgetCollection.values())
            {
                item->hide();
            }

            emit headerClosed();
        }
        else
        {
            headerButton->setArrowType(Qt::ArrowType::DownArrow);
            foreach(auto item, widgetCollection.values())
            {
                item->show();
            }

            emit headerOpened();
        }

        isOpen = !isOpen;
    });
}
