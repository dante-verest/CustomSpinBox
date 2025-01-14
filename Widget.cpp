#include "Widget.h"

#include <QVBoxLayout>
#include <QKeyEvent>
#include <QMouseEvent>

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
    // qDebug("Precess Widget' event filter! %d", ++count);
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Escape)
        {
            qInfo("ESC key pressed!");
            this->close();
        }
    }
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::MouseButton::LeftButton)
        {
            qInfo("Left mouse button pressed!");
            this->m_pCustomSpinBox->clearFocus();
        }
    }
    return QWidget::eventFilter(watched, event);
}
