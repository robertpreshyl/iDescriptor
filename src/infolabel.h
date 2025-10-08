#ifndef INFOLABEL_H
#define INFOLABEL_H

#include <QLabel>
#include <QTimer>

class InfoLabel : public QLabel
{
    Q_OBJECT

public:
    explicit InfoLabel(const QString &text = QString(),
                       QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event) override;

private slots:
    void restoreOriginalText();

private:
    QString m_originalText;
    QTimer *m_restoreTimer;
};

#endif // INFOLABEL_H