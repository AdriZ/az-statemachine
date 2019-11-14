#include "autoscaled_pix.h"

AutoscaledPix::AutoscaledPix(QWidget *parent) :
    QLabel(parent)
{
}

void AutoscaledPix::setPixmap(QString filename)
{
    m_pixmap.load(filename);
    scaledPixmap();
}

void AutoscaledPix::setPixmap(QPixmap pixmap)
{
    m_pixmap = pixmap;
    scaledPixmap();
}

void AutoscaledPix::resizeEvent(QResizeEvent *event)
{
    scaledPixmap();
}

void AutoscaledPix::scaledPixmap()
{
    if ( ! m_pixmap.isNull() )
    {
        m_scaled_pixmap = m_pixmap.scaled(QSize(width(), height()), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QLabel::setPixmap(m_scaled_pixmap);
    }
}
