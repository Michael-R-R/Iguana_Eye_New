#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class EWGlslPlainTextEdit;

class EWGlslSrcEditor : public QWidget
{
    Q_OBJECT

    QVBoxLayout* vMainLayout;
    QLabel* titleLabel;
    EWGlslPlainTextEdit* textEdit;

public:
    EWGlslSrcEditor(const QString& title, QWidget* parent = nullptr);
    ~EWGlslSrcEditor() {}

    void clear();
    void setModifiedStatus(const bool val);

public slots:
    void setTextContent(const QString& text);
    QString getTextContent();

private slots:
    void modificationUpdated(bool val);

signals:
    void modified(const bool val);
};

