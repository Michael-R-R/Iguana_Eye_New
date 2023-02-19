#include "EWFetchUserInput.h"
#include "InputContainer.h"

EWFetchUserInput::EWFetchUserInput(const InputContainer* input, QWidget* parent) :
    QDialog(parent),
    inputContainer(input),
    vLayout(new QVBoxLayout(this)), hLayout(new QHBoxLayout()),
    confirmButton(new QPushButton("Confirm", this)),
    cancelButton(new QPushButton("Cancel", this)),
    pressedInputLabel(new QLabel(this)),
    errorMsgLabel(new QLabel(this)),
    recordedModifier(-1), recordedKey(-1), isValidKeySequence(false)
{
    this->setWindowTitle("Enter input...");
    this->resize(300, 100);
    this->setModal(true);
    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                         Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);

    vLayout->addWidget(pressedInputLabel);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(errorMsgLabel);

    hLayout->addWidget(confirmButton);
    hLayout->addWidget(cancelButton);

    confirmButton->setFocusPolicy(Qt::NoFocus);
    confirmButton->setEnabled(false);
    connect(confirmButton, &QPushButton::clicked, this, &QDialog::accept);

    cancelButton->setFocusPolicy(Qt::NoFocus);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    errorMsgLabel->setStyleSheet("color: #940500;"); // Dark red
}

EWFetchUserInput::~EWFetchUserInput()
{

}

void EWFetchUserInput::mousePressEvent(QMouseEvent* event)
{
    recordedModifier = event->modifiers();
    recordedKey = convertKey(event->button());

    processPressedInput(recordedModifier, recordedKey);
}

void EWFetchUserInput::keyPressEvent(QKeyEvent* event)
{
    recordedModifier = event->modifiers();
    recordedKey = convertKey(event->key());

    processPressedInput(recordedModifier, recordedKey);
}

void EWFetchUserInput::processPressedInput(int mod, int key)
{
    if(hasDuplicateBinding(mod, key))
    {
        isValidKeySequence = false;

        QString errorMsg = "Hotkey already bound to: " + inputContainer->getKey(mod, key);
        errorMsgLabel->setText(errorMsg);
    }
    else
    {
        isValidKeySequence = (key > 0) ? true : false;
        errorMsgLabel->clear();
    }

    QKeySequence keySequence(mod | key);
    pressedInputLabel->setText(convertText(keySequence.toString(), key));
    confirmButton->setEnabled(isValidKeySequence);
}

bool EWFetchUserInput::hasDuplicateBinding(const int mod, const int key)
{
    return (inputContainer->doesExist(mod, key));
}

int EWFetchUserInput::convertKey(int key)
{
    switch(key)
    {
    case 33: { return '1'; }
    case 64: { return '2'; }
    case 35: { return '3'; }
    case 36: { return '4'; }
    case 37: { return '5'; }
    case 94: { return '6'; }
    case 38: { return '7'; }
    case 42: { return '8'; }
    case 40: { return '9'; }
    case 41: { return '0'; }
    case 95: { return '-'; }
    case 43: { return '='; }
    case 123: { return '['; }
    case 125: { return ']'; }
    case 124: { return '\\'; }
    case 58: { return ';'; }
    case 34: { return '\''; }
    case 60: { return ','; }
    case 62: { return '.'; }
    case 63: { return '/'; }
    case 126: { return '`'; }
    case 16777248: { return 0; }
    case 16777249: { return 0; }
    case 16777251: { return 0; }
    default: { return key; }
    }
}

QString EWFetchUserInput::convertText(QString text, int key)
{
    switch(key)
    {
    case 1:
    {
        text = text.first(text.lastIndexOf('+') + 1);
        text = text.append("LMB");
        return text;
    }
    case 2:
    {
        text = text.first(text.lastIndexOf('+') + 1);
        text = text.append("RMB");
        return text;
    }
    case 4:
    {
        text = text.first(text.lastIndexOf('+') + 1);
        text = text.append("MMB");
        return text;
    }
    default: { return text; }
    }
}
