#ifndef LOADINGSPINNERWIDGET_H
#define LOADINGSPINNERWIDGET_H

#include <QColor>
#include <QTimer>
#include <QWidget>

class LoadingSpinnerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoadingSpinnerWidget(QWidget *parent = nullptr);
    void setColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateRotation();

private:
    QTimer m_timer;
    int m_angle;
    QColor m_color;
};

#endif // LOADINGSPINNERWIDGET_H