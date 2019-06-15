#include "tkarp.h"
#include<iostream>
#include<time.h>
#include <QGraphicsSceneMouseEvent>
#include<QTime>
#include<QTimer>


#include <QList>
static const double Pi = 3.14159265358979323846264338327950288419717;
TKarp::TKarp(QPointF _point, QGraphicsScene *_scene, QList<QGraphicsItem *> *_listOfKarp, QList<QGraphicsItem*> *_listOfPike, QList<QGraphicsLineItem *> *_listOfAquarium):

    TFish(_point, 1, Qt::green,_scene)
    {
   this->setRotation(getAngle());  /// set primary angle

   this->setPos(getPoint());  /// set primary possition
    scene->addItem(this); /// add fish
    listOfKarp=_listOfKarp;
    listOfPike=_listOfPike;
    listOfAquarium=_listOfAquarium;
    prioritySpeed=0;
}



void TKarp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPolygon polygon;


            polygon << QPoint(15,0) << QPoint( -15,-10) << QPoint(-15,10);
            painter->setBrush(getColor());
            painter->drawPolygon(polygon);

            Q_UNUSED(option);
            Q_UNUSED(widget);

}







bool TKarp::lookDanger(){
    QList<QGraphicsItem *> pikes = scene->items(QPolygonF()
                                                          << mapToScene(15, 0)
                                                          << mapToScene(300, 130)
                                                          << mapToScene(300, -130));
int minLengthToDanger=INT_MAX;
QLineF lineToDanger;
bool flagDanger =false;
    foreach (QGraphicsItem *item, pikes) {
        foreach (QGraphicsItem *danger, *listOfPike) {

                if(item==danger){
                    QLineF tempLineToDanger(QPointF(15,0),mapFromScene(danger->pos()));

                    if(tempLineToDanger.length()<minLengthToDanger ){
                       minLengthToDanger=tempLineToDanger.length();
                      lineToDanger=tempLineToDanger;
                }
                   flagDanger=true;
                   break;                }

        }
    }
    if(flagDanger){
       // qreal angleToDanger=lineToDanger.angle()-normalizeAngle(getAngle);
        
        setAngle(getAngle()+180+qrand()%50-25);
        setSpeed(2);

        prioritySpeed=300;
        return true;
        
        


    }
return false;
}

void TKarp::look(){

    if(priorityMove())return;
    if(lookLandSpace(listOfAquarium))return;
    if(lookDanger())return;
    if(lookFriend(listOfKarp))return;
    randomMove();
    if(prioritySpeed>0){
        setSpeed(2);
        prioritySpeed--;
    }
}

void TKarp::advance(int phase){
    look();
    setRotation(getAngle());
    setPos(mapToParent(getSpeed(),0));
    Q_UNUSED(phase);
}


TKarp::~TKarp(){

}
