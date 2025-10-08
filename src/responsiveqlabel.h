#ifndef RESPONSIVEQLABEL_H
#define RESPONSIVEQLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>

class ResponsiveQLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ResponsiveQLabel(QWidget *parent = nullptr);
    void setPixmap(const QPixmap &pixmap);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void updateScaledPixmap();

    QPixmap m_originalPixmap;
    QPixmap m_scaledPixmap;
};

#endif // RESPONSIVEQLABEL_H