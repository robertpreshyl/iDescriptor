#include "loadingspinnerwidget.h"
#include <QPainter>

LoadingSpinnerWidget::LoadingSpinnerWidget(QWidget *parent)
    : QWidget(parent), m_angle(0), m_color(Qt::gray)
{
    connect(&m_timer, &QTimer::timeout, this,
            &LoadingSpinnerWidget::updateRotation);
    m_timer.setInterval(15); // Update every 15ms for smooth animation
    m_timer.start();
    setFixedSize(24, 24); // Default size
}

void LoadingSpinnerWidget::setColor(const QColor &color)
{
    m_color = color;
    update(); // Trigger a repaint with the new color
}

void LoadingSpinnerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int penWidth = 2;
    QRectF rect(penWidth / 2.0, penWidth / 2.0, width() - penWidth,
                height() - penWidth);

    QPen pen(m_color);
    pen.setWidth(penWidth);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);

    // Draw a 270-degree arc, rotating the start angle
    painter.drawArc(rect, m_angle * 16, 270 * 16);
}

void LoadingSpinnerWidget::updateRotation()
{
    m_angle = (m_angle + 10) % 360;
    update(); // Schedule a repaint
}