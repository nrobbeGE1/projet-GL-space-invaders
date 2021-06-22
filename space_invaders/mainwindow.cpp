#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), scene(new QGraphicsScene), vaisseau_joueur(new vaisseau)
{
    ui->setupUi(this);

    connect(event(keyPressEvent(QKeyEvent *event)), &QKeyEvent::KeyPress, this, &vaisseau::timerEvent);
    scene->setSceneRect(-300, -300, 600, 600);
    scene->addItem(vaisseau_joueur);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

