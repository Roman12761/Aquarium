#include "tpike.h"
#include "QPointF"
#include<iostream>
#include "tkarp.h"
#include<time.h>
#include <QGraphicsSceneMouseEvent>
#include <qmath.h>
#include<QTimer>

static const double Pi = 3.14159265358979323846264338327950288419717;
static const QColor satedPike(154,16,16);
static const QColor hungryPike(Qt::red);
TPike::TPike(QPointF _point, QGraphicsScene *_scene,
             QList< QGraphicsItem* > *_listOfKarp,
QList< QGraphicsItem*> *_listOfPike,
QList< QGraphicsLineItem* > *_listOfAquarium )
    :TFish(_point,1.5/*speed*/, Qt::red/*color*/,_scene )

{
satedPikeTimer = new QTimer;
connect(satedPikeTimer, SIGNAL(timeout()),this,SLOT(stayHungry()));
        //   this->setTransformOriginPoint(getPoint());    ///set point from rotation fish

    this->setRotation(getAngle());  ///set primary angle

    this->setPos(getPoint());  /// set primary possition

     scene->addItem(this); ///add fish

     listOfKarp=_listOfKarp;
     listOfPike=_listOfPike;
     listOfAquarium=_listOfAquarium;


}
void TPike::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPolygon polygon;
            QPoint point;
            point=getPoint().toPoint();
            polygon <<QPoint(15,0)
                    <<QPoint(-15,10)
                    <<QPoint(0,0)
                    <<QPoint(-15,-10);

            painter->setBrush(getColor());
            painter->drawPolygon(polygon);
            Q_UNUSED(option);
            Q_UNUSED(widget);
}





void TPike::eating(QGraphicsItem* karp){

    this->setColor(satedPike);
    scene->removeItem(karp);
    listOfKarp->removeOne(karp);
    satedPikeTimer->start(0.25*60*1000);

}

void TPike::stayHungry(){
    satedPikeTimer->stop();
    setColor(hungryPike);

}



bool TPike::lookEat(){
    if(getColor()==satedPike)return false;
    /// Описуємо область в якій об'єкт "бачить" потенційну жертву ///
    QList<QGraphicsItem *> eats = scene->items(QPolygonF()
                                               << mapToScene(15, 0)
                                               << mapToScene(200, 90)
                                               << mapToScene(200, -90));


    qreal minLengthToEat=INT_MAX;
    QLineF lineToEat; /// Відрізок від об'єкта до найближчої жертви, в системі відліку об'єкта ///
    bool flagEat=false;
    /// Проходимо циклом по всіх елементах які потрапили в вище описану область ///
    /// і шукаємо серед них ті що входять в список карпів ///
    foreach(QGraphicsItem * item , eats ){
        foreach(QGraphicsItem * karp, *listOfKarp){
            if(item==karp){
                QLineF tempLineToEat(QPointF(15,0),mapFromScene(karp->pos()));
                if(tempLineToEat.length()<13){

                    eating(karp);
                    setSpeed(0.2);
                    return true;


                }
                if(tempLineToEat.length()<minLengthToEat ){
                    minLengthToEat=tempLineToEat.length();
                    lineToEat=tempLineToEat;
                }
                flagEat=true;
                break;
            }
        }
    }
    /// Якшо знайдений хоч один карп направляєм об'єкт до нього  ///
    /// і збільшуємо шкидкість   ///
    if(flagEat){

        qreal angleForEat=lineToEat.angle()-normalizeAngle(this->getAngle());
        setAngle(getAngle()-angleForEat);
        setSpeed(3);
        return true;
    }
    return false;
}








void TPike::look(){
    if(priorityMove())return;
if(lookLandSpace(listOfAquarium))return;
if(lookEat())return;
if(lookFriend(listOfPike))return;
randomMove();


}



void TPike::advance(int step){

    look();
    setRotation(getAngle());
    setPos(mapToParent(getSpeed(),0));
    Q_UNUSED(step);
}
