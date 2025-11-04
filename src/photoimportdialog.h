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

#ifndef PHOTOIMPORTDIALOG_H
#define PHOTOIMPORTDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QStringList>
#include <QVBoxLayout>

class SimpleHttpServer;

class PhotoImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PhotoImportDialog(const QStringList &files, bool hasDirectories,
                               QWidget *parent = nullptr);
    ~PhotoImportDialog();

private slots:
    void init();
    void onServerStarted();
    void onServerError(const QString &error);
    void onDownloadProgress(const QString &fileName, int bytesDownloaded,
                            int totalBytes);

private:
    QStringList selectedFiles;
    bool containsDirectories;

    QListWidget *fileList;
    QLabel *warningLabel;
    QLabel *qrCodeLabel;
    QLabel *instructionLabel;
    QPushButton *m_cancelButton;
    QProgressBar *progressBar;
    QLabel *progressLabel;

    SimpleHttpServer *m_httpServer;

    void setupUI();
    void generateQRCode(const QString &url);
    QString getLocalIP() const;
};

#endif // PHOTOIMPORTDIALOG_H
