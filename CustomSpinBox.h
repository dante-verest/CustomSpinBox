#ifndef CUSTOMSPINBOX_H
#define CUSTOMSPINBOX_H

#include <QSpinBox>
#include <QRegularExpressionValidator>

class CustomSpinBox : public QSpinBox
{
    Q_OBJECT
private:
    QRegularExpressionValidator* m_pRegExpValidator;

public:
    CustomSpinBox(QWidget *parent = nullptr);

    QValidator::State validate(QString &input, int &pos) const override;
};

#endif // CUSTOMSPINBOX_H
