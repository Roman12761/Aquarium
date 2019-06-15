#ifndef TPIKE_H
#define TPIKE_H

#include "tfish.h"
#include "tkarp.h"
#include <QTimer>

class TPike : public TFish
{
    Q_OBJECT
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;

public:
    TPike(QPointF _point, QGraphicsScene *_scene, QList<QGraphicsItem *> *_listOfKarp, QList< QGraphicsItem *> *_listOfPike, QList< QGraphicsLineItem* > *_listOfAquarium );

    void advance(int step)override;

private:
    QTimer *satedPikeTimer;
    void look();

    bool lookEat();/// перевірка чи в полі зору жертва
    void eating(QGraphicsItem *karp);/// "з'їдання жертви"



    QList< QGraphicsItem* > *listOfKarp;
    QList< QGraphicsItem*> *listOfPike;
    QList< QGraphicsLineItem* > *listOfAquarium;
private slots:
    void stayHungry();
};

#endif // TPIKE_H
