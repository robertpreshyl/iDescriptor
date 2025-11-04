/*
 * iDescriptor: A free and open-source idevice management tool.
 *
 * Copyright (C) 2025 Uncore <https://github.com/uncor3>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "responsiveqlabel.h"
#include <QDebug>
#include <QPainter>

ResponsiveQLabel::ResponsiveQLabel(QWidget *parent) : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
    setScaledContents(false);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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
    if (m_originalPixmap.isNull()) {
        return;
    }

    // Use the minimum width as the constraint for scaling
    int targetWidth = qMax(minimumWidth(), width());

    // Scale the pixmap while maintaining aspect ratio
    m_scaledPixmap =
        m_originalPixmap.scaled(targetWidth, QWIDGETSIZE_MAX,
                                Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Resize the widget to match the scaled pixmap size
    // This prevents the widget from taking up more space than the actual image
    if (!m_scaledPixmap.isNull()) {
        setFixedSize(m_scaledPixmap.size());
    }

    update();
}