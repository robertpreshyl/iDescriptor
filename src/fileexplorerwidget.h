#ifndef FILEEXPLORERWIDGET_H
#define FILEEXPLORERWIDGET_H

#include "iDescriptor.h"
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QListWidget>
#include <QMenu>
#include <QPushButton>
#include <QSplitter>
#include <QStack>
#include <QStackedWidget>
#include <QString>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <libimobiledevice/afc.h>

class FileExplorerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileExplorerWidget(iDescriptorDevice *device,
                                QWidget *parent = nullptr);

private slots:
    void onSidebarItemClicked(QTreeWidgetItem *item, int column);

private:
    QSplitter *m_mainSplitter;
    QStackedWidget *m_stackedWidget;
    afc_client_t currentAfcClient;
    QTreeWidget *m_sidebarTree;
    iDescriptorDevice *m_device;

    // Tree items
    QTreeWidgetItem *m_defaultAfcItem;
    QTreeWidgetItem *m_jailbrokenAfcItem;
    QTreeWidgetItem *m_favoritePlacesItem;

    void setupSidebar();
    void loadFavoritePlaces();
};

#endif // FILEEXPLORERWIDGET_H
