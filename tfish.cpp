#include "tfish.h"
#include <QGraphicsSceneMouseEvent>
#include<QMenu>
#include<QAction>
#include<QRadioButton>
static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

TFish::TFish(QPointF _point, qreal _speed, QColor _color/*,QGraphicsScene *_scene*/,QGraphicsScene *_scene ){
     color=_color;
     speed=_speed;
     scene=_scene;
     point=_point;
     angle=qrand()%(360*16);
     priorityLeft=0;
     priorityRight=0;



 }
bool TFish::priorityMove() {
    if(priorityLeft>0){
        setAngle(getAngle()-6);
        priorityLeft--;
           setSpeed(0.3);
        return true;
    }

    if(priorityRight>0){
        setAngle(getAngle()+6);
        priorityRight--;
        setSpeed(0.3);
        return true;
    }

    return false;

}

 void TFish::randomMove(){


     if ((qrand() % 40) == 0) {
         setAngle(getAngle()-(qrand() % 23));
     } else
         if ((qrand() % 40) == 0) {
             setAngle(getAngle()+(qrand() % 23));
         }

        setSpeed( 1);



 }

bool TFish::lookLandSpace(QList<QGraphicsLineItem*> *listOfAquarium){
    QLineF landSpace;
    bool flagLand=false;

    QList<QGraphicsItem *> lands = scene->items(QPolygonF()

                                                << mapToScene(15, 0)
                                                << mapToScene(60, -27)
                                                << mapToScene(60, 27));

    foreach(QGraphicsItem * item , lands ){
        foreach(QGraphicsLineItem* land, *listOfAquarium){
            if(item==land){
                landSpace=QLineF(mapFromScene(land->line().x2(),land->line().y2()),mapFromScene(land->line().x1(),land->line().y1()));
                flagLand=true;
                break;
            }
        }
        if(flagLand)break;
    }
    if(flagLand){


        qreal angleTOland=landSpace.angle();
        if(angleTOland<90)
        {

            setAngle(getAngle()-15);
            setSpeed(1.5);
            priorityLeft=15;
        }
        else {
            setAngle(getAngle()+15);
            setSpeed(1.5);

            priorityRight=15;
        }

        return true;
    }

    return false;

}

//}

QRectF TFish::boundingRect()const{
    QPointF topLeft(/*point.x()*/-15, /*point.y()*/-10),
            bottomRight(/*point.x()+*/15,/*point.y()+*/10);

    return QRectF(topLeft,bottomRight);
}

bool TFish::lookFriend(QList<QGraphicsItem*> *listOfFriend){

    QList<QGraphicsItem *> friends = scene->items(QPolygonF()
                                                  << mapToScene(15, 0)
                                                  << mapToScene(60, -27)
                                                  << mapToScene(60, 27));

    bool flagFriend=false;

    QPointF priorityFriend;
    foreach(QGraphicsItem * item , friends ){
        if(item==this)continue;
        foreach(QGraphicsItem * _friend, *listOfFriend){

            if(item==_friend){
                priorityFriend=mapFromScene(_friend->pos());
                flagFriend=true;
                break;
            }
        }
    }


    if(flagFriend){
        if(priorityFriend.y()<0)
        {
            setAngle(getAngle()+20);
            setSpeed(1.5);
            setPriorityRight(4);

        }
        else
        {
            setAngle(getAngle()-20);
            setSpeed(1.5);
            setPriorityLeft(4);
        }
        return true;
    }
return false;
}



QPointF TFish::getPoint()const{
    return point;
}
void TFish::setAngle(qreal _angle){
    angle=_angle;
}

QColor TFish::getColor()const{
    return color;
}

qreal TFish::getAngle()const{
    return angle;
}
qreal TFish::normalizeAngle(qreal _angle)
{
    while (_angle < 0)
        _angle += TwoPi;
    while (_angle > TwoPi)
        _angle -= TwoPi;
    return _angle;
}

qreal TFish::getSpeed() const
{
    return speed;
}

void TFish::setSpeed(qreal value)
{
    speed = value;
}

void TFish::setColor(const QColor &value)
{
    color = value;
}

int TFish::getPriorityLeft() const
{
    return priorityLeft;
}

void TFish::setPriorityLeft(int value)
{
    priorityLeft = value;
}

int TFish::getPriorityRight() const
{
    return priorityRight;
}

void TFish::setPriorityRight(int value)
{
    priorityRight = value;
}
