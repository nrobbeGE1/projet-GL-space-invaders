#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), scene(new QGraphicsScene), Ennemi{new ennemi(1),new ennemi(2), new ennemi(3), new ennemi(4),new ennemi(5),new ennemi(6), new ennemi(7), new ennemi(8),new ennemi(9),new ennemi(10), new ennemi(11), new ennemi(12),new ennemi(13),new ennemi(14), new ennemi(15)}
{

    ui->setupUi(this);
    for (int i=0; i<15; i++){
        scene->addItem(Ennemi[i]);
    }
    ui->graphicsView->setScene(scene);
    scene ->setSceneRect(-300, -300, 600, 600);

}

MainWindow::~MainWindow()
{
    delete ui;
}

