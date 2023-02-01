#include "SelectAppOptionsWidget.h"
#include "EditorHotkeyTableWidget.h"

SelectAppOptionsWidget::SelectAppOptionsWidget(QWidget* parent) :
    QWidget(parent),
    hMainLayout(new QHBoxLayout(this)),
    vOptionSelectLayout(new QVBoxLayout()),
    vContentAreaLayout(new QVBoxLayout()),
    gameGroupBox(new QGroupBox("Game", this)), gameGroupLayout(new QVBoxLayout(gameGroupBox)),
    editorGroupBox(new QGroupBox("Editor", this)), editorGroupLayout(new QVBoxLayout(editorGroupBox)),
    contentWidget(nullptr)
{
    vOptionSelectLayout->addWidget(gameGroupBox);
    vOptionSelectLayout->addWidget(editorGroupBox);

    hMainLayout->addLayout(vOptionSelectLayout);
    hMainLayout->addLayout(vContentAreaLayout);
}

SelectAppOptionsWidget::~SelectAppOptionsWidget()
{

}

void SelectAppOptionsWidget::setupGameGroupBox(InputContainer* input)
{
    gameGroupBox->setAlignment(Qt::AlignHCenter);

    auto gameHotkeysButton = new QPushButton("Hotkeys", gameGroupBox);
    connect(gameHotkeysButton, &QPushButton::clicked, gameHotkeysButton, [this]()
    {
        delete contentWidget;
        contentWidget = nullptr;
    });

    gameGroupLayout->addWidget(gameHotkeysButton);
    gameGroupLayout->addStretch(1);
}

void SelectAppOptionsWidget::setupEditorGroupBox(InputContainer* input)
{
    editorGroupBox->setAlignment(Qt::AlignHCenter);

    auto editorHotkeysButton = new QPushButton("Hotkeys", editorGroupBox);
    connect(editorHotkeysButton, &QPushButton::clicked, editorHotkeysButton, [this, input]()
    {
        delete contentWidget;
        contentWidget = new EditorHotkeyTableWidget(input, this);
        vContentAreaLayout->addWidget(contentWidget);
    });

    editorGroupLayout->addWidget(editorHotkeysButton);
    editorGroupLayout->addStretch(1);
}
