#include "devicependingwidget.h"
#include <QLabel>
#include <QVBoxLayout>

DevicePendingWidget::DevicePendingWidget(QWidget *parent) : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);

    QLabel *label = new QLabel("Please click on trust on the popup", this);

    layout->addWidget(label);
    setLayout(layout);
}
