#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include "tkarp.h"
#include <QMouseEvent>
#include "tpike.h"
#include <QList>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:


void mousePressEvent(QMouseEvent *event) ; /// Перехоплення лівого кліку мишки
/// слоти що відповідають за опрацювання натискання клавіш
private slots:
    void on_start_clicked();

    void on_addPike_clicked();

    void on_addKarp_clicked();

    void on_clear_clicked();

    void on_pause_clicked();


    void on_pushButton_clicked();

private:
    QString whichFish; /// допоміжна змінна яка запам'ятовує яка кнопка натиснута останньою(додати коропа чи щуку)
    QTimer *timer; /// таймер що для ігрового циклу
    QGraphicsScene *scene; /// сцена
    QList< QGraphicsItem* > listOfKarp; /// список коропів
    QList< QGraphicsItem*> listOfPike; /// список щук
    QList< QGraphicsLineItem* > listOfAquarium; /// список ліній з яких складається ландшафт

    void addLineToAquarium(QLineF line, QColor color); /// функція яка малює лінії на сцені

  Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
