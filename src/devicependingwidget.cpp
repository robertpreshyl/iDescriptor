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

#include "devicependingwidget.h"
#include <QLabel>
#include <QVBoxLayout>

DevicePendingWidget::DevicePendingWidget(bool locked, QWidget *parent)
    : QWidget{parent}, m_label{nullptr}, m_locked{locked}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);

    m_label = new QLabel(m_locked ? "Please unlock the screen"
                                  : "Please click on trust on the popup",
                         this);

    layout->addWidget(m_label);
    setLayout(layout);
}

void DevicePendingWidget::next()
{
    m_label->setText("Please click on trust on the popup");
}