#ifndef MYRECTANGLE_H
#define MYRECTANGLE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "window.h"
#include "convertirhora.h"
class Window;
class Estructura;

//#include "middle.h"

class Rectangulo : public QGraphicsItem, public ConvertirHora
{
public:
    Rectangulo();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool Pressed;
    void posandscale(qreal x, qreal y, qreal width, qreal height);
    void name_posFligth(QString text,float x);
    void setScene(QGraphicsScene *s);
    void datos(int ta, int nav, int npi, QString fe, QString *noV, QString *ori, QString *des, QString *pi, float *ini, float *fin, QString *avi, int taAr, Estructura *est);
    void setPosArray(int i);
    float calculateTime(float pos);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual QVariant    itemChange ( GraphicsItemChange change, const QVariant & value );



private:
    QGraphicsScene *scene;

    int posX;
    int posY;
    int posXCurrent;
    int posYCurrent;
    int tamWidth;
    int tamHeight;
    float posText;
    QString fligth;
    QRectF rec;
//    Middle *middle;
    Window *w;
    QRectF sceneRec;
    QRectF perimetro;
    QString retrasoString;
    float retrasoFloat;
    int posArray;

    QString fecha;
    QString *nomVuelo;
    QString *origen;
    QString *destino;
    float *hInicio;
    float *hFin;
    QString *piloto;
    QString *avion;

    int numeroAviones;
    int numeroPilotos;
    int tam;
    int tamArchivo;

    Estructura *estructura;
};

#endif // MYRECTANGLE_H
