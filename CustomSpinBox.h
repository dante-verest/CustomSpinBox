#ifndef CUSTOMSPINBOX_H
#define CUSTOMSPINBOX_H

#include <QSpinBox>
#include <QTimeEdit>
#include <QMap>
#include <QRegularExpressionValidator>

class CustomSpinBox : public QDateTimeEdit
{
    Q_OBJECT
private:
    const QString timeFormat = "hh:mm";
    QString sign;
    QString timeFormatWithSign;
    int stateUTC; // 1 when up, -1 when down, 0 not defined
    const QMap<QPair<int, int>, QString> utcZones = {
        {{-12, 00}, "Etc/GMT+12"},
        {{-11, 00}, "Etc/GMT+11"},
        {{-10, 00}, "Etc/GMT+10"},
        {{-9, 30}, "Patific/Marquesas"},
        {{-9, 00}, "Etc/GMT+9"},
        {{-8, 00}, "Etc/GMT+8"},
        {{-7, 00}, "Etc/GMT+7"},
        {{-6, 00}, "Etc/GMT+6"},
        {{-5, 00}, "Etc/GMT+5"},
        {{-4, 00}, "Etc/GMT+4"},
        {{-3, 30}, "Canada/Newfoundland"},
        {{-3, 00}, "Etc/GMT+3"},
        {{-2, 00}, "Etc/GMT+2"},
        {{-1, 00}, "Etc/GMT+1"},
        {{+0, 00}, "Etc/GMT-0"},
        {{+1, 00}, "Etc/GMT-1"},
        {{+2, 00}, "Etc/GMT-2"},
        {{+3, 00}, "Etc/GMT-3"},
        {{+3, 30}, "Asia/Tehran"},
        {{+4, 00}, "Etc/GMT-4"},
        {{+4, 30}, "Asia/Kabul"},
        {{+5, 00}, "Etc/GMT-5"},
        {{+5, 30}, "Asia/Colombo"},
        {{+5, 45}, "Asia/Kathmandu"},
        {{+6, 00}, "Etc/GMT-6"},
        {{+6, 30}, "Asia/Yangon"},
        {{+7, 00}, "Etc/GMT-7"},
        {{+8, 00}, "Etc/GMT-8"},
        {{+8, 45}, "Australia/Eucla"},
        {{+9, 00}, "Etc/GMT-9"},
        {{+10, 00}, "Etc/GMT-10"},
        {{+10, 30}, "Australia/Adelaide"},
        {{+11, 00}, "Etc/GMT-11"},
        {{+11, 30}, "Australia/Lord_Howe"},
        {{+12, 00}, "Etc/GMT-12"},
        {{+13, 00}, "Etc/GMT-13"},
        {{+13, 45}, "Patific/Chatham"},
        {{+14, 00}, "Etc/GMT-14"}
    };

    QRegularExpressionValidator* m_pRegExpValidator;

    void step(int &hour, int &minute, bool up);

public:
    CustomSpinBox(QWidget *parent = nullptr);

    QValidator::State validate(QString &input, int &pos) const override;
    void fixup(QString &input) const override;
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // CUSTOMSPINBOX_H
