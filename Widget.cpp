#include "Widget.h"

#include <QVBoxLayout>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_pCustomSpinBox{new CustomSpinBox{}}
{
    this->m_pCustomSpinBox->setGeometry(this->size().height() / 2,
                                        this->size().width() / 2,
                                        200,
                                        40);

    QHBoxLayout mainLayout{this};
    mainLayout.addWidget(this->m_pCustomSpinBox);

    this->installEventFilter(this);
}

Widget::~Widget() {}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Escape)
        {
            qInfo("ESC key pressed!");
            this->close();
        }
    }
    return QWidget::eventFilter(watched, event);
}
