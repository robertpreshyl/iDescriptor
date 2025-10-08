#include "fileexplorerwidget.h"
#include "afcexplorerwidget.h"
#include "iDescriptor-ui.h"
#include "iDescriptor.h"
#include "mediapreviewdialog.h"
#include "settingsmanager.h"
#include <QApplication>
#include <QDebug>
#include <QDesktopServices>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QIcon>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
#include <QPainter>
#include <QPalette>
#include <QPushButton>
#include <QSignalBlocker>
#include <QSplitter>
#include <QSplitterHandle>
#include <QTreeWidget>
#include <QVariant>
#include <libimobiledevice/afc.h>
#include <libimobiledevice/libimobiledevice.h>

FileExplorerWidget::FileExplorerWidget(iDescriptorDevice *device,
                                       QWidget *parent)
    : QWidget(parent), m_device(device)
{
    m_mainSplitter = new ModernSplitter(Qt::Horizontal, this);

    // Main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_mainSplitter);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    setupSidebar();

    // Create stacked widget with AFC explorers
    m_stackedWidget = new QStackedWidget();

    // Add normal AFC explorer (index 0)
    m_stackedWidget->addWidget(
        new AfcExplorerWidget(m_device->afcClient, nullptr, m_device));

    // Add AFC2 explorer (index 1)
    m_stackedWidget->addWidget(
        new AfcExplorerWidget(m_device->afc2Client, nullptr, m_device));

    // Start with normal AFC client
    m_stackedWidget->setCurrentIndex(0);

    // Add widgets to splitter
    m_mainSplitter->addWidget(m_sidebarTree);
    m_mainSplitter->addWidget(m_stackedWidget);
    m_mainSplitter->setSizes({400, 800});
    setLayout(mainLayout);
}
void FileExplorerWidget::setupSidebar()
{
    m_sidebarTree = new QTreeWidget();
    m_sidebarTree->setHeaderLabel("Files");
    m_sidebarTree->setMinimumWidth(50);
    m_sidebarTree->setMaximumWidth(250);

    QTreeWidgetItem *explorersRoot = new QTreeWidgetItem(m_sidebarTree);
    explorersRoot->setText(0, "Explorer");
    explorersRoot->setIcon(0, QIcon::fromTheme("folder"));
    explorersRoot->setExpanded(true);

    m_defaultAfcItem = new QTreeWidgetItem(explorersRoot);
    m_defaultAfcItem->setText(0, "Default");
    m_defaultAfcItem->setIcon(0, QIcon::fromTheme("folder"));

    m_jailbrokenAfcItem = new QTreeWidgetItem(explorersRoot);
    m_jailbrokenAfcItem->setText(0, "Jailbroken (AFC2)");
    m_jailbrokenAfcItem->setIcon(0, QIcon::fromTheme("applications-system"));

    // Common Places section
    QTreeWidgetItem *commonPlacesItem = new QTreeWidgetItem(m_sidebarTree);
    commonPlacesItem->setText(0, "Common Places");
    commonPlacesItem->setIcon(0, QIcon::fromTheme("places-bookmarks"));
    commonPlacesItem->setExpanded(true);

    QTreeWidgetItem *wallpapersItem = new QTreeWidgetItem(commonPlacesItem);
    wallpapersItem->setText(0, "Wallpapers");
    wallpapersItem->setIcon(0, QIcon::fromTheme("image-x-generic"));
    wallpapersItem->setData(0, Qt::UserRole,
                            "../../../var/mobile/Library/Wallpapers");

    // Favorite Places section
    m_favoritePlacesItem = new QTreeWidgetItem(m_sidebarTree);
    m_favoritePlacesItem->setText(0, "Favorite Places");
    m_favoritePlacesItem->setIcon(0, QIcon::fromTheme("user-bookmarks"));
    m_favoritePlacesItem->setExpanded(true);

    loadFavoritePlaces();

    connect(m_sidebarTree, &QTreeWidget::itemClicked, this,
            &FileExplorerWidget::onSidebarItemClicked);
}

void FileExplorerWidget::loadFavoritePlaces()
{
    SettingsManager *settings = SettingsManager::sharedInstance();
    QList<QPair<QString, QString>> favorites = settings->getFavoritePlaces();
    qDebug() << "Loading favorite places:" << favorites.size();
    for (const auto &favorite : favorites) {
        QString path = favorite.first;
        QString alias = favorite.second;

        qDebug() << "Favorite:" << alias << "->" << path;
        QTreeWidgetItem *favoriteItem =
            new QTreeWidgetItem(m_favoritePlacesItem);
        favoriteItem->setText(0, alias);
        favoriteItem->setIcon(0, QIcon::fromTheme("folder-favorites"));
        favoriteItem->setData(0, Qt::UserRole, QVariant::fromValue(path));
    }
}

void FileExplorerWidget::onSidebarItemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    if (item == m_defaultAfcItem) {
        m_stackedWidget->setCurrentIndex(0);
    } else if (item == m_jailbrokenAfcItem) {
        m_stackedWidget->setCurrentIndex(1);
    }
    // TODO: implement favorite places
}