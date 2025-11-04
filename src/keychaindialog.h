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

#ifndef KEYCHAIN_DIALOG_H
#define KEYCHAIN_DIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QMediaPlayer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVideoWidget>

class KeychainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeychainDialog(QWidget *parent = nullptr);
    ~KeychainDialog();

private slots:
    void onOkClicked();
    void onSkipSigningInClicked();

private:
    void setupUI();
    void setupVideo();

    QMediaPlayer *m_player;
    QVideoWidget *m_videoWidget;
    QVBoxLayout *m_mainLayout;
    QPushButton *m_okButton;
    QPushButton *m_skipSigningInButton;
    QLabel *m_titleLabel;
    QLabel *m_descriptionLabel;
    QCheckBox *m_dontShowAgainCheckbox;
};

#endif // KEYCHAIN_DIALOG_H