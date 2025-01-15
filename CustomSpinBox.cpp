#include "CustomSpinBox.h"

#include <QLineEdit>
#include <QKeyEvent>
// #include <QDateTimeEdit>

/*
 * Нужно смотреть qdatetime.cpp и qdatetimeedit.cpp
 */

// void CustomSpinBox::step(int &hour, int &minute, bool up)
// {
//     switch(hour) {
//     case -9:
//         if(minute == 30) {
//             if(up) {
//                 stepBy(29);
//             } else {
//                 stepBy(-29);
//             }
//         }
//         break;
//     case -3:

//         break;
//     case +3:

//         break;
//     case +5:

//         break;
//     case +6:

//         break;
//     case +8:

//         break;
//     case +10:

//         break;
//     case +13:

//         break;
//     default:
//         break;
//     }
// }

CustomSpinBox::CustomSpinBox(QWidget *parent)
    : QAbstractSpinBox{parent}
    // , stateUTC{1}
{
    this->installEventFilter(this);

    this->sign = "+";
    // this->timeFormatWithSign = this->sign + this->timeFormat;
    // this->setDisplayFormat(this->timeFormatWithSign);
    this->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::PlusMinus);
    this->lineEdit()->setAlignment(Qt::AlignCenter);
    // this->setSelectedSection(QDateTimeEdit::Section::HourSection);
    // this->setMaximumTime(QTime(14, 0));
    this->setWrapping(true);
    this->setCurrentValue(QPair<int, int>{3, 0});
    this->selectAll();
    this->lineEdit()->setReadOnly(true);

    // QDateTime local(QDateTime::currentDateTime());
    // qDebug() << "Local time is:" << local;
    // QDateTime UTC(local);
    // UTC.setTimeSpec(Qt::OffsetFromUTC);
    // qDebug() << "UTC time is:" << UTC;
    // qDebug() << "There are" << local.secsTo(UTC) << "seconds difference between the datetimes.";
    // // UTC.timeRepresentation();
    // qDebug() << "offset" << UTC.offsetFromUtc();
    // // UTC.setOffsetFromUtc(-7200);
    // qDebug() << "offset" << UTC.offsetFromUtc();
    // qDebug() << "There are" << local.secsTo(UTC) << "seconds difference between the datetimes. 2";
    // qDebug() << "2 UTC time is:" << UTC.toOffsetFromUtc(-7200);
}

QValidator::State CustomSpinBox::validate(QString &input, int &pos) const
{
    // QValidator::State state = QValidator::State::Acceptable;
    qDebug() << "input to validate" << input << "and pos" << pos;
    // int hour = QDateTime::fromString(input, timeFormatWithSign).time().hour();
    // int minute = QDateTime::fromString(input, timeFormatWithSign).time().minute();
    // qDebug() << hour << minute;
    // qDebug() << "current section" << this->currentSection();
    // QPair<int, int> zone{hour, minute};
    // QMap<QPair<int, int>, QString>::const_iterator utcZoneFind = utcZones.find(zone);
    // if(utcZoneFind != utcZones.end()) {
    //     qDebug() << "FIND!";
    //     state = QValidator::State::Acceptable;
    // } else {
    //     state = QValidator::State::Invalid;
    //     // this->interpretText();
    // }
    // if(state != QValidator::State::Acceptable) {
    //     // input = this->sign + QString::number(hour) + ":00";
    // }
    // return state;

    // return QDateTimeEdit::validate(input, pos);

    return QAbstractSpinBox::validate(input, pos);
}

void CustomSpinBox::fixup(QString &input) const
{
    // qDebug() << "fixup: invalid text" << input;
    // int hour = QDateTime::fromString(input, timeFormatWithSign).time().hour();
    // input = this->sign + QString::number(hour) + ":00";
    // qDebug() << "fixup: valid text" << input;
    // QDateTimeEdit::fixup(input);

    QAbstractSpinBox::fixup(input);
}

void CustomSpinBox::stepDown()
{
    this->stepBy(-1);
}

void CustomSpinBox::stepUp()
{
    this->stepBy(1);
}

bool CustomSpinBox::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Down)
        {
            qDebug("Key DOWN pressed!");
            // if(this->currentSection() == QDateTimeEdit::Section::HourSection) {
            //     int hour = this->time().hour();
            //     qDebug() << "hour section DOWN! hour" << hour;
            //     if(hour == 0 && this->stateUTC == 1) {
            //         qDebug() << "!!!DOWN!!!";
            //         // this->stepBy(1);
            //         this->stateUTC = -1;
            //         this->sign = "-";
            //         this->timeFormatWithSign = this->sign + this->timeFormat;
            //         this->setDisplayFormat(this->timeFormatWithSign);
            //         this->setMaximumTime(QTime(12, 0));
            //     } else if(this->stateUTC == -1) {
            //         qDebug() << "inverted DOWN!";
            //         // this->stepBy(2);
            //     }
            //     if(this->time().hour() == this->maximumTime().hour()) {
            //         qDebug() << "!!!MAXIMUM HOUR!!!";
            //         // this->stateUTC = 1;
            //         // this->timeFormatWithSign = "+" + this->timeFormat;
            //         // this->setDisplayFormat(this->timeFormatWithSign);
            //         // this->setMaximumTime(QTime(14, 0));
            //         // this->setTime(QTime(this->minimumTime().hour(), 0));
            //     }
            //     this->setSelectedSection(QDateTimeEdit::Section::HourSection);
            // }
            // if(this->currentSection() == QDateTimeEdit::Section::MinuteSection) {
            //     this->stepBy(-14);
            // }
            this->stepDown();
            this->selectAll();
            qDebug() << "output" << this->currentValue() << this->utcZones.value(this->currentValue());
        }
        if(keyEvent->key() == Qt::Key_Up)
        {
            qDebug("Key UP pressed!");
            // if(this->currentSection() == QDateTimeEdit::Section::HourSection) {
            //     int hour = this->time().hour();
            //     qDebug() << "hour section UP! hour" << hour;
            //     if(hour == 0 && this->stateUTC == -1) {
            //         qDebug() << "!!!UP!!!";
            //         // this->stepBy(-1);
            //         this->stateUTC = 1;
            //         this->sign = "+";
            //         this->timeFormatWithSign = this->sign + this->timeFormat;
            //         this->setDisplayFormat(this->timeFormatWithSign);
            //         this->setMaximumTime(QTime(14, 0));
            //     } else if(this->stateUTC == 1) {
            //         qDebug() << "inverted UP!";
            //         // this->stepBy(-2);
            //     }
            //     if(this->time().hour() == this->maximumTime().hour()) {
            //         qDebug() << "!!!MAXIMUM HOUR!!!";
            //         this->stateUTC = -1;
            //         // this->timeFormatWithSign = "-" + this->timeFormat;
            //         // this->setDisplayFormat(this->timeFormatWithSign);
            //         // this->setMaximumTime(QTime(12, 0));
            //         // this->setTime(QTime(this->maximumTime().hour(), 0));
            //         // this->interpretText();
            //     }
            //     this->setSelectedSection(QDateTimeEdit::Section::HourSection);
            // }
            // if(this->currentSection() == QDateTimeEdit::Section::MinuteSection) {
            //     this->stepBy(14);
            // }
            this->stepUp();
            this->selectAll();
            qDebug() << "output" << this->currentValue() << this->utcZones.value(this->currentValue());
        }
    }
    // return QDateTimeEdit::eventFilter(watched, event);
    return QAbstractSpinBox::eventFilter(watched, event);
}

void CustomSpinBox::stepBy(int steps)
{
    QMap<QPair<int, int>, QString>::const_iterator mapIterator = this->utcZones.find(this->m_currentValue);
    if(steps == -1) {
        --mapIterator;
        if(mapIterator == this->utcZones.cbegin())
            mapIterator = this->utcZones.find(this->utcZones.lastKey());
        this->setCurrentValue(mapIterator.key());
    } else if(steps == 1) {
        ++mapIterator;
        if(mapIterator == this->utcZones.cend())
            mapIterator = this->utcZones.find(this->utcZones.firstKey());
        this->setCurrentValue(mapIterator.key());
    }
}

QPair<int, int> CustomSpinBox::currentValue() const
{
    return m_currentValue;
}

void CustomSpinBox::setCurrentValue(const QPair<int, int> &newCurrentValue)
{
    if (m_currentValue == newCurrentValue)
        return;
    m_currentValue = newCurrentValue;
    int hour = m_currentValue.first;
    int minute = m_currentValue.second;
    if(hour < 0)
        this->sign = "-";
    else
        this->sign = "+";
    this->lineEdit()->setText(QString("UTC " +
                                      this->sign +
                                      (std::abs(hour) < 10 ? QString("0%1").arg(std::abs(hour)) : QString::number(std::abs(hour))) +
                                      ":" +
                                      (minute < 10 ? QString("0%1").arg(minute) : QString::number(minute))));
    emit currentValueChanged();
}
