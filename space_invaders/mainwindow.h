#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include "vaisseau.h"
#include "projectile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Vaisseau *vaisseau_joueur;
    Projectile *tir_joueur;
};
#endif // MAINWINDOW_H
