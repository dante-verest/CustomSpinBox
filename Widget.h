#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QEvent>

#include "CustomSpinBox.h"

class Widget : public QWidget
{
    Q_OBJECT
private:
    CustomSpinBox *m_pCustomSpinBox;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    bool eventFilter(QObject *watched, QEvent *event) override;
};
#endif // WIDGET_H
