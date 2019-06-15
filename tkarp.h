 #ifndef TKARP_H
#define TKARP_H

#include "tfish.h"
#include <QList>


class TKarp : public TFish
{
    Q_OBJECT

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;

public:
    TKarp(QPointF _point, QGraphicsScene *_scene,
          QList<QGraphicsItem*> *_listOfKarp,
          QList<QGraphicsItem*> *_listOfPike,
          QList< QGraphicsLineItem*> *_listOfAquarium);

    void advance(int step) override;/// функція яка викликається таймером і відповідає за рух
    void look();/// перегляд і оцінка всіх об'єктів які може бачити риба
    bool lookDanger();/// перевірка чи бачить небезпеку


    virtual ~TKarp();
private:
    int prioritySpeed;
    QList< QGraphicsItem* > *listOfKarp;
    QList< QGraphicsItem *> *listOfPike;
    QList< QGraphicsLineItem* > *listOfAquarium;

};

#endif // TKARP_H
