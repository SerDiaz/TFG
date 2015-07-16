#include "rectangulo.h"
#include <Qtcore>
#include <QtGui>

#include <stdio.h>
#include <iostream>

Rectangulo::Rectangulo()
{
    Pressed = false;
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
    w=new Window();
}

void Rectangulo::setScene(QGraphicsScene *s)
{
    scene=s;
}


QRectF Rectangulo::boundingRect() const
{
    return QRectF(posX,posY,tamWidth,tamHeight);
}

void Rectangulo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    rec = boundingRect();
    sceneRec = scene->sceneRect();
    QBrush brush(Qt::white);



    if(Pressed){
        brush.setColor(Qt::red);

        painter->fillRect(rec,brush);
        painter->drawRect(rec);

        float posTime=posX;
        float posXCurrentMap=posXCurrent+posX;
        if(posXCurrentMap>posX && posXCurrentMap <=sceneRec.right()-50){
            posTime=posXCurrentMap;
        }else if(posXCurrentMap>sceneRec.right()-50){
            posTime=sceneRec.right()-50;
        }

        retrasoFloat=calculateTime(posTime);
        if(retrasoFloat<0){
            retrasoFloat=0;
        }

        retrasoString=aString(retrasoFloat);
        painter->drawText((posX+(tamWidth/posText)),posY+3.5,30,30,0,retrasoString);





    }else{
        brush.setColor(Qt::white);

        painter->fillRect(rec,brush);
        painter->drawRect(rec);
        painter->drawText((posX+(tamWidth/posText)),posY+3.5,30,30,0,fligth);
        retrasoFloat=0;

    }

}


void Rectangulo::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Rectangulo::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);


    if(retrasoString!="00:00"){
        w->setDatos(tam,numeroAviones,numeroPilotos,fecha,nomVuelo,origen,destino,piloto,hInicio,hFin,avion,tamArchivo,estructura);
        w->reordenarEstructura(nomVuelo[posArray],retrasoFloat);
    }

}



void Rectangulo::posandscale(qreal x, qreal y, qreal width, qreal height){
    posX=x;
    posY=y;
    tamHeight=height;
    tamWidth=width;
}

void Rectangulo::name_posFligth(QString text,float x)
{
    fligth = text;
    posText=x;
}

QVariant Rectangulo::itemChange ( GraphicsItemChange change, const QVariant & value )
{
    if (change == ItemPositionChange && scene) {

        // value is the new position.
        QPointF newPos = value.toPointF();
        // marca el perimetro
        perimetro=QRectF(0,0,sceneRec.right()-posX-50,sceneRec.top());


        posXCurrent = newPos.x();
        posYCurrent = newPos.y();

        if (!perimetro.contains(newPos)) {
            newPos.setX(qMin(perimetro.right(), qMax(newPos.x(), perimetro.left())));
            newPos.setY(qMin(perimetro.bottom(), qMax(newPos.y(), perimetro.top())));
            return newPos;
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void Rectangulo::datos(int ta, int nav, int npi, QString fe, QString *noV, QString *ori, QString *des, QString *pi, float *ini, float *fin, QString *avi, int taAr, Estructura *est){
    tam=ta;
    numeroAviones=nav;
    numeroPilotos=npi;
    fecha=fe;
    avion = avi;
    nomVuelo=noV;
    origen=ori;
    destino=des;
    hInicio=ini;
    hFin=fin;
    piloto=pi;
    tamArchivo=taAr;
    estructura=est;
}

void Rectangulo::setPosArray(int i)
{
    posArray=i;
}

float Rectangulo::calculateTime(float pos)
{
    float anchoColumna=38.85;
    float inicioRectangle=anchoColumna/2;
    float nuevaHora=6+(((pos/inicioRectangle)-1)/4);
    float retraso=nuevaHora-hInicio[posArray];
    return retraso;
}
