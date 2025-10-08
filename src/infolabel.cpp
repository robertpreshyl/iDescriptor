#include "infolabel.h"
#include <QApplication>
#include <QClipboard>
#include <QMouseEvent>

InfoLabel::InfoLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent), m_originalText(text)
{
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("QLabel:hover { background-color: rgba(255, 255, 255, 0.1); "
                  "border-radius: 2px; }");

    m_restoreTimer = new QTimer(this);
    m_restoreTimer->setSingleShot(true);
    connect(m_restoreTimer, &QTimer::timeout, this,
            &InfoLabel::restoreOriginalText);
}

void InfoLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(m_originalText);

        setText("Copied!");
        setStyleSheet("QLabel { color: #4CAF50; font-weight: bold; } "
                      "QLabel:hover { background-color: rgba(255, 255, 255, "
                      "0.1); border-radius: 2px; }");

        m_restoreTimer->start(1000); // Show "Copied!" for 1 second
    }
    QLabel::mousePressEvent(event);
}

void InfoLabel::enterEvent(QEnterEvent *event)
{
    if (!m_restoreTimer->isActive()) {
        setStyleSheet("QLabel:hover { background-color: rgba(255, 255, 255, "
                      "0.1); border-radius: 2px; }");
    }
    QLabel::enterEvent(event);
}

void InfoLabel::leaveEvent(QEvent *event)
{
    if (!m_restoreTimer->isActive()) {
        setStyleSheet("QLabel:hover { background-color: rgba(255, 255, 255, "
                      "0.1); border-radius: 2px; }");
    }
    QLabel::leaveEvent(event);
}

void InfoLabel::restoreOriginalText()
{
    setText(m_originalText);
    setStyleSheet("QLabel:hover { background-color: rgba(255, 255, 255, 0.1); "
                  "border-radius: 2px; }");
}
