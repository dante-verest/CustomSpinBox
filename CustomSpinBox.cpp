#include "CustomSpinBox.h"

#include <QLineEdit>
#include <QKeyEvent>
// #include <QDateTimeEdit>

/*
 * Нужно смотреть qdatetime.cpp и qdatetimeedit.cpp
 */

void CustomSpinBox::step(int &hour, int &minute, bool up)
{
    switch(hour) {
    case -9:
        if(minute == 30) {
            if(up) {
                stepBy(29);
            } else {
                stepBy(-29);
            }
        }
        break;
    case -3:

        break;
    case +3:

        break;
    case +5:

        break;
    case +6:

        break;
    case +8:

        break;
    case +10:

        break;
    case +13:

        break;
    default:
        break;
    }
}

CustomSpinBox::CustomSpinBox(QWidget *parent)
    : QDateTimeEdit{parent}
    // , d{new QDateTimeEditPrivate}
    , stateUTC{0}
    , m_pRegExpValidator{new QRegularExpressionValidator{this}}
{
    this->installEventFilter(this);

    // this->d = reinterpret_cast<QDateTimeEditPrivate*>(QDateTimeEdit::d_ptr.data());

    this->timeFormatWithSign = "+" + this->timeFormat;
    this->setDisplayFormat(this->timeFormatWithSign);
    // this->m_pRegExpValidator->setRegularExpression(QRegularExpression("\\d{1}(?:[,.]{1})\\d*"));
    // this->m_pRegExpValidator->setRegularExpression(QRegularExpression("^(?:[ \\t]+(\\d\\d):(\\d\\d):(\\d\\d))?"));
    // this->lineEdit()->setValidator(this->m_pRegExpValidator);
    this->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::PlusMinus);
    this->lineEdit()->setAlignment(Qt::AlignCenter);
    this->setSelectedSection(QDateTimeEdit::Section::HourSection);
    // this->setTimeRange(QTime(-12, 0), QTime(14, 0));
    this->setMaximumTime(QTime(14, 0));
    // this->setMinimumTime(QTime(-12, 0));
    // this->stepDown();
    this->setWrapping(true);

    QDateTime local(QDateTime::currentDateTime());
    qDebug() << "Local time is:" << local;
    QDateTime UTC(local);
    UTC.setTimeSpec(Qt::OffsetFromUTC);
    qDebug() << "UTC time is:" << UTC;
    qDebug() << "There are" << local.secsTo(UTC) << "seconds difference between the datetimes.";
    // UTC.timeRepresentation();
    qDebug() << "offset" << UTC.offsetFromUtc();
    // UTC.setOffsetFromUtc(-7200);
    qDebug() << "offset" << UTC.offsetFromUtc();
    qDebug() << "There are" << local.secsTo(UTC) << "seconds difference between the datetimes. 2";
    qDebug() << "2 UTC time is:" << UTC.toOffsetFromUtc(-7200);
}

QValidator::State CustomSpinBox::validate(QString &input, int &pos) const
{
    QValidator::State state = QValidator::State::Acceptable;
    qDebug() << "input to validate" << input << "and pos" << pos;
    int hour = QDateTime::fromString(input, timeFormatWithSign).time().hour();
    int minute = QDateTime::fromString(input, timeFormatWithSign).time().minute();
    qDebug() << hour << minute;
    QPair<int, int> zone{hour, minute};
    QMap<QPair<int, int>, QString>::const_iterator utcZoneFind = utcZones.find(zone);
    if(utcZoneFind != utcZones.end()) {
        qDebug() << "FIND!";
        state = QValidator::State::Acceptable;
    } else {
        state = QValidator::State::Invalid;
        // this->interpretText();
    }
    if(state != QValidator::State::Acceptable) {
        // input = this->sign + QString::number(hour) + ":00";
    }
    // return QDateTimeEdit::validate(input, pos);
    return state;
}

void CustomSpinBox::fixup(QString &input) const
{
    qDebug() << "fixup: invalid text" << input;
    int hour = QDateTime::fromString(input, timeFormatWithSign).time().hour();
    input = this->sign + QString::number(hour) + ":00";
    QDateTimeEdit::fixup(input);
}

bool CustomSpinBox::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Down)
        {
            qDebug("Key DOWN pressed!");
            if(this->currentSection() == QDateTimeEdit::Section::HourSection) {
                int hour = this->time().hour();
                qDebug() << "hour section DOWN! hour" << hour;
                if(hour == 0) {
                    qDebug() << "down";
                    // this->stepBy(1);
                    this->stateUTC = -1;
                    this->timeFormatWithSign = "-" + this->timeFormat;
                    this->setDisplayFormat(this->timeFormatWithSign);
                    this->setMaximumTime(QTime(12, 0));
                } else if(this->stateUTC == -1) {
                    qDebug() << "inverted DOWN!";
                    // this->stepBy(2);
                }
                this->setSelectedSection(QDateTimeEdit::Section::HourSection);
            }
            if(this->currentSection() == QDateTimeEdit::Section::MinuteSection) {
                this->stepBy(-14);
            }
        }
        if(keyEvent->key() == Qt::Key_Up)
        {
            qDebug("Key UP pressed!");
            if(this->currentSection() == QDateTimeEdit::Section::HourSection) {
                int hour = this->time().hour();
                qDebug() << "hour section UP! hour" << hour;
                if(hour == 0) {
                    qDebug() << "up";
                    // this->stepBy(-1);
                    this->stateUTC = 1;
                    this->timeFormatWithSign = "+" + this->timeFormat;
                    this->setDisplayFormat(this->timeFormatWithSign);
                    this->setMaximumTime(QTime(14, 0));
                } else if(this->stateUTC == 1) {
                    qDebug() << "inverted UP!";
                    // this->stepBy(-2);
                }
                this->setSelectedSection(QDateTimeEdit::Section::HourSection);
            }
            if(this->currentSection() == QDateTimeEdit::Section::MinuteSection) {
                this->stepBy(14);
            }
        }
        // qDebug() << "UTC" << this->dateTime().offsetFromUtc();
        // qDebug() << "time spec" << this->timeSpec();
        // qDebug() << "time zone" << this->timeZone();
        // qDebug() << "5" << this->dateTime() << "but" << this->text();
    }
    return QDateTimeEdit::eventFilter(watched, event);
}
