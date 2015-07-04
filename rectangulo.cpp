#include "rectangulo.h"
#include <Qtcore>
#include <QtGui>

#include <stdio.h>
#include <iostream>

Rectangulo::Rectangulo()
{
    Pressed = false;
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);

}

void Rectangulo::setScene(QGraphicsScene *s)
{
    scene=s;
}


QRectF Rectangulo::boundingRect() const
{
//    return QRectF(0,0,scene->width(),scene->height());
    return QRectF(posX,posY,tamWidth,tamHeight);
}

void Rectangulo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    rec = boundingRect();
//    rec = QRectF(posX,posY,tamWidth,tamHeight);
    sceneRec = scene->sceneRect();
    QBrush brush(Qt::white);



    if(Pressed){
        brush.setColor(Qt::red);

        painter->fillRect(rec,brush);
        painter->drawRect(rec);
        QString hola="hola";

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
//        std::cout << "retrasoFloat: " << retrasoFloat << std::endl;
        retrasoString=aString(retrasoFloat);
//        std::cout << "retrasoString: " << retrasoString.toStdString() << std::endl;

//        QString re=QString::number(retrasoFloat);
        painter->drawText((posX+(tamWidth/posText)),posY+3.5,30,30,0,retrasoString);





    }else{
        brush.setColor(Qt::white);

        painter->fillRect(rec,brush);
        painter->drawRect(rec);
        painter->drawText((posX+(tamWidth/posText)),posY+3.5,30,30,0,fligth);

    }









}


void Rectangulo::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
    w=new Window();

    std::cout << "posX: " << posX << std::endl;
    std::cout << "sceneRec.right()-posX: " << sceneRec.right()-posX << std::endl;
    std::cout << "sceneRec.right()-posXCurrent: " << sceneRec.right()-posXCurrent << std::endl;
    std::cout << "sceneRec.right(): " << sceneRec.right() << std::endl;

}

void Rectangulo::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
    std::cout << "posXCurrent: " << posXCurrent << std::endl;



//    std::cout << "posYCurrent: " << posYCurrent << std::endl;
//    middle = new Middle();
//    crear();
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

////        **************
//        int derecha=sceneRec.right();
//        int izquierda=sceneRec.left();
//        int bottom=sceneRec.bottom();
//        int top=sceneRec.top();
//        std::cout << "sceneRect rigth: " << derecha << std::endl;
//        std::cout << "sceneRect left: " << izquierda << std::endl;
//        std::cout << "sceneRect top: " << top << std::endl;
//        std::cout << "sceneRect bottom: " << bottom << std::endl;

//        derecha=rec.right();
//        izquierda=rec.left();
//        bottom=rec.bottom();
//        top=rec.top();
//        std::cout << "rec rigth: " << derecha << std::endl;
//        std::cout << "rec left: " << izquierda << std::endl;
//        std::cout << "rec top: " << top << std::endl;
//        std::cout << "rec bottom: " << bottom << std::endl;

//        derecha=perimetro.right();
//        izquierda=perimetro.left();
//        bottom=perimetro.bottom();
//        top=perimetro.top();
//        std::cout << "perimetro rigth: " << derecha << std::endl;
//        std::cout << "perimetro left: " << izquierda << std::endl;
//        std::cout << "perimetro top: " << top << std::endl;
//        std::cout << "perimetro bottom: " << bottom << std::endl;

//        herencia();




        posXCurrent = newPos.x();
        posYCurrent = newPos.y();
//        w->setTimeToMenu(posXCurrent);
//        std::cout << "posXCurrent: " << posXCurrent << std::endl;
//        std::cout << "posYCurrent: " << posYCurrent << std::endl;
//        **************


        if (!perimetro.contains(newPos)) {
            //            newPos.setX(qMin(rect.right() - tamWidth, qMax(newPos.x() , rect.left() + tamWidth/2)));
            //            newPos.setY(qMin(rect.bottom() - tamHeight/2, qMax(newPos.y() , rect.top() + tamHeight/2)));
            // Keep the item inside the scene rect.
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

//int derecha=rec.right();
//int izquierda=rec.left();
//int bottom=rec.bottom();
//int top=rec.top();


//std::cout << "derecha: " << derecha << std::endl;
//std::cout << "izquierda: " << izquierda << std::endl;
//std::cout << "top: " << bottom << std::endl;
//std::cout << "bottom: " << top << std::endl;

//int xPos=newPos.x();
//int yPos=newPos.y();

//std::cout << "xPos: " << xPos << std::endl;
//std::cout << "yPos: " << yPos << std::endl;
