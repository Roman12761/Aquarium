#include "taquarium.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <QTime>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer;
    whichFish="None";
    ui->setupUi(this);

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    this->setWindowTitle("Aquarium");
    scene = new QGraphicsScene();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

       ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
      ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
       ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
       ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали
        QRectF sceneRect(0,0,1585,830);
        scene->setSceneRect(sceneRect); /// Устанавливаем область графической сцены

/// paint aquarium
scene->setBackgroundBrush(Qt::blue);  ///set background

       addLineToAquarium(QLineF(sceneRect.topLeft(),sceneRect.topRight()),Qt::black);
       addLineToAquarium(QLineF(sceneRect.bottomLeft(),sceneRect.topLeft()),Qt::black);
       addLineToAquarium(QLineF(sceneRect.topRight(),sceneRect.bottomRight()),Qt::black);
       addLineToAquarium(QLineF(sceneRect.bottomRight(),sceneRect.bottomLeft()),Qt::black);
      /// Create List of Group Karp

   connect(timer,SIGNAL(timeout()), scene,SLOT(advance()));





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{

        timer->start(1000 / 33);
}



void MainWindow::addLineToAquarium(QLineF line, QColor color ){

    QGraphicsLineItem *line1=new QGraphicsLineItem(line);
            listOfAquarium.append(line1);
            line1->setPen(color);
           scene->addItem(line1);
}

//    foreach (TKarp *k, *listOfGroupKarp[0]) {
//        k->move();
//    }




void MainWindow::on_addPike_clicked()
{
    whichFish.clear();
    whichFish="Pike";
}

void MainWindow::on_addKarp_clicked()
{
    whichFish.clear();
    whichFish="Karp";
}



void MainWindow::mousePressEvent(QMouseEvent *event){
   if(whichFish=="None")return;

    QPointF point=ui->graphicsView->mapToScene(event->pos());  /// координати мишки

    if(whichFish=="Pike"){
         if(listOfPike.size()==3)return;
         TPike *pike=new TPike(point,scene, &listOfKarp,&listOfPike,&listOfAquarium);
         listOfPike.append(pike);


   }
   if(whichFish=="Karp"){
      if(listOfKarp.size()==10)return;
        TKarp *karp=new TKarp(point,scene,&listOfKarp,&listOfPike,&listOfAquarium);
        listOfKarp.append(karp);
          }

}

void MainWindow::on_clear_clicked()
{
    timer->stop();
    foreach (QGraphicsItem *p, listOfPike) {

                scene->removeItem(p);   /// видаляєм зі сцени
                listOfPike.removeOne(p);     /// Delete from list
                delete  p;               /// Free memories

        }
    foreach (QGraphicsItem *k, listOfKarp) {

        scene->removeItem(k);   /// видаляєм зі сцени
        listOfPike.removeOne(k);     /// Delete from list
        delete  k;
        }




}

void MainWindow::on_pause_clicked()
{
timer->stop();
}



void MainWindow::on_pushButton_clicked()
{
    QMessageBox *box = new QMessageBox;

    box->setText("Aquarium\nPowered by Roman Movchenyuk\nStudent of Yrui Fed'kovich Chernivtsi national university\n");

    box->show();
    //delete box;
}
