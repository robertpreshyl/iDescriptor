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

#include "mountdevimagewidget.h"
#include "appcontext.h"
#include <QPushButton>
// #include "./core/services/mount_dev_image.cpp"
#include <QDebug>
#include <QVBoxLayout>
MountDevImageWidget::MountDevImageWidget(QString udid, QWidget *parent)
    : QWidget{parent}
{
    iDescriptorDevice *device =
        AppContext::sharedInstance()->getDevice(udid.toStdString());

    // Add mount button
    QPushButton *mountButton = new QPushButton("Mount Developer Disk Image");
    // connect(mountButton, &QPushButton::clicked, this, [this, device]()
    //         {
    //         if (device->lockdownClient == nullptr || device->device ==
    //         nullptr)
    //         {
    //             qDebug() << "Device not initialized properly, cannot mount
    //             disk image."; return;
    //         }
    //         lockdownd_client_t lckd = device->lockdownClient;
    //         idevice_t idevice = device->device;
    //         afc_client_t afc = device->afcClient;
    //         lockdownd_service_descriptor_t service = device->lockdownService;
    //         int ret = mount_dev_image(lckd, service, afc, idevice);
    //         qDebug() << "Mounting developer disk image returned: " << ret;
    //         });

    setLayout(new QVBoxLayout);
    layout()->addWidget(mountButton);
    layout()->setAlignment(mountButton, Qt::AlignCenter);
}
