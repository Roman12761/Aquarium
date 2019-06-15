#ifndef TFISH_H
#define TFISH_H
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QMainWindow>
#include<QPoint>
#include<QRectF>
#include <QGraphicsLineItem>
class TFish : public QObject,public QGraphicsItem
{
    Q_OBJECT
protected:

    QRectF boundingRect() const override;

public:



    TFish(QPointF _point,  qreal _speed, QColor _color, QGraphicsScene *_scene);

    bool lookLandSpace(QList<QGraphicsLineItem*> *listOfAquarium); ///перегляд ландшафту перед рибою

    bool lookFriend(QList<QGraphicsItem*> *listOfFriend);/// перегляд риб спільного типу

    bool priorityMove();/// допоміжна функція повороту

    void randomMove(); ///псевдорандомний рух

    qreal normalizeAngle(qreal _angle);

    QPointF getPoint()const;

    QColor getColor()const;

    qreal getAngle()const;

    void setAngle(qreal _angle);

    qreal getSpeed() const;

    void setSpeed(qreal value);
    void setColor(const QColor &value);

    int getPriorityLeft() const;
    void setPriorityLeft(int value);

    int getPriorityRight() const;
    void setPriorityRight(int value);


private:
     int priorityLeft;
     int priorityRight;
     QPointF point;
     qreal speed;
     QColor color;
   qreal angle;
protected:
   QGraphicsScene *scene;




};

#endif // TFISH_H
