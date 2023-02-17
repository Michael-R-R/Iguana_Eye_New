#include "EWSelectApplicationOption.h"
#include "EWGameHotkeyTable.h"
#include "EWEditorHotkeyTable.h"

EWSelectApplicationOption::EWSelectApplicationOption(QWidget* parent) :
    QWidget(parent),
    hMainLayout(new QHBoxLayout(this)),
    vOptionSelectLayout(new QVBoxLayout()),
    vContentAreaLayout(new QVBoxLayout()),
    gameGroupBox(new QGroupBox("Game", this)), gameGroupLayout(new QVBoxLayout(gameGroupBox)),
    editorGroupBox(new QGroupBox("Editor", this)), editorGroupLayout(new QVBoxLayout(editorGroupBox)),
    contentWidget(new QWidget(this))
{
    vOptionSelectLayout->addWidget(gameGroupBox);
    vOptionSelectLayout->addWidget(editorGroupBox);

    vContentAreaLayout->addWidget(contentWidget);

    hMainLayout->addLayout(vOptionSelectLayout);
    hMainLayout->addLayout(vContentAreaLayout);
}

EWSelectApplicationOption::~EWSelectApplicationOption()
{

}

void EWSelectApplicationOption::setupGameGroupBox(InputContainer* input)
{
    gameGroupBox->setAlignment(Qt::AlignHCenter);

    auto gameHotkeysButton = new QPushButton("Hotkeys", gameGroupBox);
    connect(gameHotkeysButton, &QPushButton::clicked, gameHotkeysButton, [this, input]()
    {
        delete contentWidget;
        contentWidget = new EWGameHotkeyTable(input, this);
        vContentAreaLayout->addWidget(contentWidget);
    });

    gameGroupLayout->addWidget(gameHotkeysButton);
    gameGroupLayout->addStretch(1);
}

void EWSelectApplicationOption::setupEditorGroupBox(InputContainer* input)
{
    editorGroupBox->setAlignment(Qt::AlignHCenter);

    auto editorHotkeysButton = new QPushButton("Hotkeys", editorGroupBox);
    connect(editorHotkeysButton, &QPushButton::clicked, editorHotkeysButton, [this, input]()
    {
        delete contentWidget;
        contentWidget = new EWEditorHotkeyTable(input, this);
        vContentAreaLayout->addWidget(contentWidget);
    });

    editorGroupLayout->addWidget(editorHotkeysButton);
    editorGroupLayout->addStretch(1);
}
