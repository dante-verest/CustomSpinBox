#ifndef CUSTOMSPINBOX_H
#define CUSTOMSPINBOX_H

#include <QSpinBox>
#include <QTimeEdit>
#include <QMap>
// #include <unordered_map>
#include <map>
// #include <QHash>
// #include <QSet>

// template<typename _T1, typename _T2>
// _GLIBCXX_CONSTEXPR bool
// operator<(const QPair<_T1, _T2>& __x, const QPair<_T1, _T2>& __y)
// {
//     qDebug() << "operator <";
//     if(__x.first < 0 && __y.first < 0)
//         return __x.first < __y.first
//                || (!(__y.first < __x.first) && !(__x.second < __y.second));
//     else
//         return __x.first < __y.first
//                || (!(__y.first < __x.first) && __x.second < __y.second);
// }

class CustomSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
    Q_PROPERTY(QPair<int, int> currentValue READ currentValue WRITE setCurrentValue NOTIFY currentValueChanged FINAL)

private:
    // const QString timeFormat = "hh:mm";
    QString sign;
    // QString timeFormatWithSign;
    // int stateUTC; // 1 when up, -1 when down, 0 not defined
    // struct hash_pair {
    //     template <class T1, class T2>
    //     size_t operator()(const std::pair<T1, T2>& p) const
    //     {
    //         // Hash the first element
    //         size_t hash1 = std::hash<T1>{}(p.first);
    //         // Hash the second element
    //         size_t hash2 = std::hash<T2>{}(p.second);
    //         // Combine the two hash values
    //         // что это за смещения вообще?
    //         return hash1
    //                ^ (hash2 + 0x9e3779b9 + (hash1 << 6)
    //                   + (hash1 >> 2));
    //     }
    // };

    // template<typename _T1, typename _T2>
    // inline _GLIBCXX_CONSTEXPR bool
    // operator==(const QPair<_T1, _T2>& __x, const QPair<_T1, _T2>& __y)
    // {
    //     return __x.first == __y.first && __x.second == __y.second;
    // }

    /// Uses @c operator== to find the result.
    // template<typename _T1, typename _T2>
    // inline _GLIBCXX_CONSTEXPR bool
    // operator!=(const QPair<_T1, _T2>& __x, const QPair<_T1, _T2>& __y)
    // {
    //     return !(__x == __y);
    // }

    /// Uses @c operator< to find the result.
    // template<typename _T1, typename _T2>
    // inline _GLIBCXX_CONSTEXPR bool
    // operator>(const QPair<_T1, _T2>& __x, const QPair<_T1, _T2>& __y)
    // {
    //     return __y < __x;
    // }

    /// Uses @c operator< to find the result.
    // template<typename _T1, typename _T2>
    // inline _GLIBCXX_CONSTEXPR bool
    // operator<=(const QPair<_T1, _T2>& __x, const QPair<_T1, _T2>& __y)
    // {
    //     return !(__y < __x);
    // }

    /// Uses @c operator< to find the result.
    // template<typename _T1, typename _T2>
    // inline _GLIBCXX_CONSTEXPR bool
    // operator>=(const QPair<_T1, _T2>& __x, const QPair<_T1, _T2>& __y)
    // {
    //     return !(__x < __y);
    // }

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

    QPair<int, int> m_currentValue;

public:
    CustomSpinBox(QWidget *parent = nullptr);

    QValidator::State validate(QString &input, int &pos) const override;
    void fixup(QString &input) const override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    void stepBy(int steps) override;
    void stepDown();
    void stepUp();

    QPair<int, int> currentValue() const;
    void setCurrentValue(const QPair<int, int> &newCurrentValue = {+3, 00});

signals:
    void currentValueChanged();
};

#endif // CUSTOMSPINBOX_H
