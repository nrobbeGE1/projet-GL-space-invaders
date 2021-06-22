#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include "vaisseau.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /*void keyPressEvent(QKeyEvent *event) {
        switch(event->key()) {
        case Qt::Key_Q:
            qDebug("Gauche");
            vaisseau::timerEvent(*event);
            break;
         case Qt::Key_D:
            qDebug("Droite");
            break;
        }
    }*/

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;      //on dit au programme sur quelle scene travailler
    vaisseau *vaisseau_joueur;      //on lui dit quel objet on utilise
};
#endif // MAINWINDOW_H
