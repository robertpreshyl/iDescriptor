#include "responsiveqlabel.h"
#include <QDebug>
#include <QPainter>

ResponsiveQLabel::ResponsiveQLabel(QWidget *parent) : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
    setScaledContents(false);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    setMinimumSize(100, 100);
}

void ResponsiveQLabel::setPixmap(const QPixmap &pixmap)
{
    m_originalPixmap = pixmap;
    updateScaledPixmap();
}

void ResponsiveQLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    if (!m_originalPixmap.isNull()) {
        updateScaledPixmap();
    }
}

void ResponsiveQLabel::paintEvent(QPaintEvent *event)
{
    if (m_scaledPixmap.isNull()) {
        QLabel::paintEvent(event);
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Calculate position to center the pixmap
    int x = (width() - m_scaledPixmap.width()) / 2;
    int y = (height() - m_scaledPixmap.height()) / 2;

    painter.drawPixmap(x, y, m_scaledPixmap);
}

void ResponsiveQLabel::updateScaledPixmap()
{
    if (m_originalPixmap.isNull() || size().isEmpty()) {
        return;
    }

    // Scale the pixmap while maintaining aspect ratio
    m_scaledPixmap = m_originalPixmap.scaled(size(), Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation);

    update();
}