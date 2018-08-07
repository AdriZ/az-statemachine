/**
 * @file
 *  D�finit la classe AutoscaledPix qui permet de cr�er des images
 *  se redimentionnant automatiquement en conservant leurs proportions.
 */

#ifndef AUTOSCALED_PIX_H
#define AUTOSCALED_PIX_H

#include <QLabel>
#include <QPixmap>

/** Permet de cr�er des images se redimentionnant automatiquement
    en conservant leurs proportions */
class AutoscaledPix : public QLabel
{
public:
    explicit AutoscaledPix(QWidget *parent=0);

    /**
     * D�finit l'image qui doit �tre affich�e.
     *
     * @param[in] filename
     *      Fichier contenant l'image � afficher.
     */
    void setPixmap(QString filename);

    /**
     * D�finit l'image qui doit �tre affich�e.
     *
     * @param[in] pixmap
     *      Image � afficher.
     */
    void setPixmap(QPixmap pixmap);

    /**
     * Retourne l'image affich�e.
     *
     * @return
     *      QPixmap affich�
     */
    QPixmap * getPixmap() { return &m_scaled_pixmap; }

protected:
    /**
     * Ev�nement appel� automatiquement lors du redimentionnement du widget.
     */
    void resizeEvent(QResizeEvent *event);

private:
    /** Image � afficher */
    QPixmap m_pixmap;
    /** Image affich�e une fois redimentionn�e */
    QPixmap m_scaled_pixmap;

    /** Redimentionne et affiche l'image */
    void scaledPixmap();
};

#endif // AUTOSCALED_PIX_H
