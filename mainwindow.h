#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "ennemi.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   void timerEvent(QTimerEvent *event) override;
   void keyPressEvent(QKeyEvent *event) override;
   void changeTexte(QGraphicsSimpleTextItem);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    ennemi *Ennemi[15];
    ennemi *Ennemi2[15];

    QGraphicsSimpleTextItem *m_text_item;

};
#endif // MAINWINDOW_H
