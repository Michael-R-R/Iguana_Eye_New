#pragma once

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>

class InputContainer;

class FetchUserInputWidget : public QDialog
{
    const InputContainer* inputContainer;

    QVBoxLayout* vLayout;
    QHBoxLayout* hLayout;

    QPushButton* confirmButton;
    QPushButton* cancelButton;

    QLabel* pressedInputLabel;
    QLabel* errorMsgLabel;

    int recordedModifier;
    int recordedKey;
    bool isValidKeySequence;

public:
    FetchUserInputWidget(const InputContainer* input, QWidget* parent = nullptr);
    ~FetchUserInputWidget();

    int getMod() { return recordedModifier; }
    int getKey() { return recordedKey; }
    QKeySequence getKeySequence() { return QKeySequence(recordedModifier | recordedKey); }

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    void processPressedInput(int mod, int key);
    bool hasDuplicateBinding(const int mod, const int key);
    int convertKey(int key);
    QString convertText(QString text, int key);
};

