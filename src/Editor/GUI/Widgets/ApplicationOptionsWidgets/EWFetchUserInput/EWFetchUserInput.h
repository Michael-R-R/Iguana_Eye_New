#pragma once

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>

class BaseInput;

class EWFetchUserInput : public QDialog
{
    // DOES NOT OWN THIS POINTER
    const BaseInput* input;

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
    EWFetchUserInput(const BaseInput* input_, QWidget* parent = nullptr);
    ~EWFetchUserInput();

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

