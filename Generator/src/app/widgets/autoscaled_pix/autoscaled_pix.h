/**
 * @file
 *  Définit la classe AutoscaledPix qui permet de créer des images
 *  se redimentionnant automatiquement en conservant leurs proportions.
 */

#ifndef AUTOSCALED_PIX_H
#define AUTOSCALED_PIX_H

#include <QLabel>
#include <QPixmap>

/** Permet de créer des images se redimentionnant automatiquement
    en conservant leurs proportions */
class AutoscaledPix : public QLabel
{
public:
    explicit AutoscaledPix(QWidget *parent=0);

    /**
     * Définit l'image qui doit être affichée.
     *
     * @param[in] filename
     *      Fichier contenant l'image à afficher.
     */
    void setPixmap(QString filename);

    /**
     * Définit l'image qui doit être affichée.
     *
     * @param[in] pixmap
     *      Image à afficher.
     */
    void setPixmap(QPixmap pixmap);

    /**
     * Retourne l'image affichée.
     *
     * @return
     *      QPixmap affiché
     */
    QPixmap * getPixmap() { return &m_scaled_pixmap; }

protected:
    /**
     * Evènement appelé automatiquement lors du redimentionnement du widget.
     */
    void resizeEvent(QResizeEvent *event);

private:
    /** Image à afficher */
    QPixmap m_pixmap;
    /** Image affichée une fois redimentionnée */
    QPixmap m_scaled_pixmap;

    /** Redimentionne et affiche l'image */
    void scaledPixmap();
};

#endif // AUTOSCALED_PIX_H
