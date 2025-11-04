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

#include "diagnosedialog.h"
#include <QApplication>

DiagnoseDialog::DiagnoseDialog(QWidget *parent) : QDialog(parent)
{
    setupUI();

    setWindowTitle("System Dependencies");
    setModal(true);
    resize(500, 400);

    // Set clean close behavior
    setAttribute(Qt::WA_DeleteOnClose, true);
}

void DiagnoseDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Add the main diagnose widget
    m_diagnoseWidget = new DiagnoseWidget();
    scrollArea->setWidget(m_diagnoseWidget);

    // Close button
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    m_closeButton = new QPushButton("Close");
    m_closeButton->setMinimumWidth(80);
    connect(m_closeButton, &QPushButton::clicked, this,
            &DiagnoseDialog::onCloseClicked);

    buttonLayout->addWidget(m_closeButton);

    // Layout assembly
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(buttonLayout);
}

void DiagnoseDialog::onCloseClicked() { accept(); }