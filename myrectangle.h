#ifndef MYRECTANGLE_H
#define MYRECTANGLE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
//class Middle;


class Myrectangle : public QGraphicsItem
{
public:
    Myrectangle();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool Pressed;
    void posandscale(qreal x, qreal y, qreal width, qreal height);
    void name_posFligth(QString text,float x);
    void setScene(QGraphicsScene *s);



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

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

};

#endif // MYRECTANGLE_H
