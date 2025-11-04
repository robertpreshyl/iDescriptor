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

#include "detailwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

DetailWindow::DetailWindow(const QString &title, int userId, QWidget *parent)
    : QMainWindow(parent), m_title(title), m_userId(userId)
{

    setWindowTitle(m_title);

    QLabel *label = new QLabel(QString("User ID: %1").arg(m_userId));
    QWidget *central = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(label);
    setCentralWidget(central);
}
