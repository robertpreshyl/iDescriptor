#include "recoverydeviceinfowidget.h"
#include "iDescriptor.h"
#include "libirecovery.h"
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

RecoveryDeviceInfoWidget::RecoveryDeviceInfoWidget(
    const iDescriptorRecoveryDevice *info, QWidget *parent)
    : QWidget{parent}
{
    ecid = info->ecid; // Assuming ecid is unique for each device
    QVBoxLayout *devLayout = new QVBoxLayout();
    devLayout->setContentsMargins(10, 10, 10, 10);
    devLayout->setSpacing(10);
    setLayout(devLayout);

    devLayout->addWidget(new QLabel("Device: Recovery Mode Device"));
    devLayout->addWidget(
        new QLabel("Actual Mode: " +
                   QString::fromStdString(parse_recovery_mode(info->mode))));
    devLayout->addWidget(new QLabel("ECID: " + QString::number(info->ecid)));
    devLayout->addWidget(new QLabel("CPID: " + QString::number(info->cpid)));
    devLayout->addWidget(new QLabel(info->displayName));

    QPushButton *exitRecoveyMode = new QPushButton("Exit Recovery Mode");
    connect(exitRecoveyMode, &QPushButton::clicked, this, [this, info]() {
        irecv_client_t client = NULL;
        irecv_error_t ierr = irecv_open_with_ecid_and_attempts(
            &client, info->ecid, RECOVERY_CLIENT_CONNECTION_TRIES);
        irecv_error_t error = IRECV_E_SUCCESS;
        if (ierr != IRECV_E_SUCCESS) {
            printf("Failed to open device with ECID %llu: %s\n", info->ecid,
                   irecv_strerror(ierr));
            return;
        }

        if (client == NULL) {
            printf("Error: client is NULL after successful open\n");
            return;
        }

        printf("Device opened successfully, sending reboot command...\n");

        error = irecv_setenv(client, "auto-boot", "true");
        if (error != IRECV_E_SUCCESS) {
            QMessageBox::critical(
                this, "Error",
                "Failed to set environment variable 'auto-boot' to 'true'");
            qDebug() << "Failed to set environment variable: "
                     << irecv_strerror(error);
        }

        error = irecv_saveenv(client);
        if (error != IRECV_E_SUCCESS) {
            QMessageBox::critical(this, "Error",
                                  "Failed to save environment variables");
            qDebug() << "Failed to save environment variables: "
                     << irecv_strerror(error);
        }

        error = irecv_reboot(client);
        if (error != IRECV_E_SUCCESS) {
            // debug("%s\n", irecv_strerror(error));
            QMessageBox::critical(this, "Error",
                                  "Failed to send reboot command");
            qDebug() << "critical to send reboot command: "
                     << irecv_strerror(error);
        }

        irecv_close(client);
    });
    devLayout->addWidget(exitRecoveyMode, 0, Qt::AlignCenter);
}
