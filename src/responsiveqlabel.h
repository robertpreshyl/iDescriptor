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

#ifndef RESPONSIVEQLABEL_H
#define RESPONSIVEQLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>

class ResponsiveQLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ResponsiveQLabel(QWidget *parent = nullptr);
    void setPixmap(const QPixmap &pixmap);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void updateScaledPixmap();

    QPixmap m_originalPixmap;
    QPixmap m_scaledPixmap;
};

#endif // RESPONSIVEQLABEL_H