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

#ifdef __APPLE__
#ifndef DISKUSAGEBAR_H
#define DISKUSAGEBAR_H

#include <QTimer>
#include <QWidget>

class DiskUsageBar : public QWidget
{
    Q_OBJECT

public:
    explicit DiskUsageBar(QWidget *parent = nullptr);

    void setUsageInfo(const QString &type, const QString &formattedSize,
                      const QString &color, double percentage);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void showPopover();

private:
    QString m_type;
    QString m_formattedSize;
    QString m_color;
    double m_percentage;
    QTimer *m_hoverTimer;
};

#endif // DISKUSAGEBAR_H
#endif // __APPLE__