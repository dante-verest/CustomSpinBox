#include "CustomSpinBox.h"

#include <QLineEdit>

/*
 * Нужно смотреть qdatetime.cpp и qdatetimeedit.cpp
 */

CustomSpinBox::CustomSpinBox(QWidget *parent)
    : QSpinBox{parent}
    , m_pRegExpValidator{new QRegularExpressionValidator{this}}
{
    // this->m_pRegExpValidator->setRegularExpression(QRegularExpression("\\d{1}(?:[,.]{1})\\d*"));
    this->m_pRegExpValidator->setRegularExpression(QRegularExpression("^(?:[ \\t]+(\\d\\d):(\\d\\d):(\\d\\d))?"));
    // this->lineEdit()->setValidator(this->m_pRegExpValidator);
    this->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::PlusMinus);
    this->lineEdit()->setAlignment(Qt::AlignCenter);
}

QValidator::State CustomSpinBox::validate(QString &input, int &pos) const
{
    QValidator::State state = this->m_pRegExpValidator->validate(input, pos);
    if (state == QValidator::Invalid) {
        return state;
    }
    return state;
}
