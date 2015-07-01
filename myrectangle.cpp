#include "myrectangle.h"
#include <Qtcore>
#include <QtGui>

#include <stdio.h>
#include <iostream>

Myrectangle::Myrectangle()
{
    Pressed = false;
//    setFlag(ItemIsMovable);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);

}

void Myrectangle::setScene(QGraphicsScene *s)
{
    scene=s;
}

QRectF Myrectangle::boundingRect() const
{
    return QRectF(posX,posY,tamWidth,tamHeight);
}

void Myrectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    rec = boundingRect();
    QBrush brush(Qt::blue);

    if(Pressed){
        brush.setColor(Qt::red);
    }else{
        brush.setColor(Qt::white);
    }

    painter->fillRect(rec,brush);
    painter->drawRect(rec);
    painter->drawText((posX+(tamWidth/posText)),posY+3.5,30,30,0,fligth);
}

void Myrectangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);

}

void Myrectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
    std::cout << "posXCurrent: " << posXCurrent << std::endl;
    std::cout << "posYCurrent: " << posYCurrent << std::endl;
//    middle = new Middle();
//    crear();

}

void Myrectangle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
//    Pressed = false;
//    update();
//    QGraphicsItem::mouseDoubleClickEvent(event);
}


void Myrectangle::posandscale(qreal x, qreal y, qreal width, qreal height){
    posX=x;
    posY=y;
    tamHeight=height;
    tamWidth=width;
}

void Myrectangle::name_posFligth(QString text,float x)
{
    fligth = text;
    posText=x;
}

QVariant Myrectangle::itemChange ( GraphicsItemChange change, const QVariant & value )
{
    if (change == ItemPositionChange && scene) {

        // value is the new position.
        QPointF newPos = value.toPointF();
        QRectF sceneRect = scene->sceneRect();

        QRectF perimetro(0,0,sceneRect.right()-posX-50,sceneRect.top());

//        **************
        int derecha=sceneRect.right();
        int izquierda=sceneRect.left();
        int bottom=sceneRect.bottom();
        int top=sceneRect.top();
        std::cout << "sceneRect rigth: " << derecha << std::endl;
        std::cout << "sceneRect left: " << izquierda << std::endl;
        std::cout << "sceneRect top: " << top << std::endl;
        std::cout << "sceneRect bottom: " << bottom << std::endl;

        derecha=rec.right();
        izquierda=rec.left();
        bottom=rec.bottom();
        top=rec.top();
        std::cout << "rec rigth: " << derecha << std::endl;
        std::cout << "rec left: " << izquierda << std::endl;
        std::cout << "rec top: " << top << std::endl;
        std::cout << "rec bottom: " << bottom << std::endl;

        derecha=perimetro.right();
        izquierda=perimetro.left();
        bottom=perimetro.bottom();
        top=perimetro.top();
        std::cout << "perimetro rigth: " << derecha << std::endl;
        std::cout << "perimetro left: " << izquierda << std::endl;
        std::cout << "perimetro top: " << top << std::endl;
        std::cout << "perimetro bottom: " << bottom << std::endl;

//        herencia();

        posXCurrent = newPos.x();
        posYCurrent = newPos.y();
//        std::cout << "posXCurrent: " << xPos << std::endl;
//        std::cout << "posYCurrent: " << yPos << std::endl;
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
