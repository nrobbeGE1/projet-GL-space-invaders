#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include "ennemi.h"
#include "vaisseau.h"
#include "projectile.h"
#include <QTimer>
#include <QList>

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
    ennemi *Ennemi[15];     //15 ennemis (1e ligne)
    ennemi *Ennemi2[15];    //15 ennemis (2e ligne)
    Vaisseau *vaisseau_joueur;      // vaisseau
    Projectile *tir_joueur;     //projectile (tir du vaisseau)
    QGraphicsSimpleTextItem *m_text_item;
    int score = 0;
};
#endif // MAINWINDOW_H
