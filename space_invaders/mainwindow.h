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
    int m_id_timer_monstre[30];
    int m_timer_window;
    bool m_premiere_fois_start = true;
    ennemi *Ennemi[15];     //15 ennemis (1e ligne)
    ennemi *Ennemi2[15];    //15 ennemis (2e ligne)
    Vaisseau *vaisseau_joueur;      //vaisseau
    Projectile *tir_joueur[5];     //projectiles (tirs du vaisseau)
    Projectile *tir_ennemi[5];    //projectiles (tirs des ennemis)
    int sel_projectile_vaisseau = 0;     //selection du projectile du vaisseau
    int sel_projectile_ennemi = 0;      //selection du projectile de l'ennemi
    QGraphicsSimpleTextItem *m_text_item;
    int m_num_score;
    QGraphicsSimpleTextItem *m_score;
    int m_num_vie;
    QGraphicsSimpleTextItem *m_vie;
    bool game_over = false;
    bool type;


    bool premier_tir_ennemi = true;
};
#endif // MAINWINDOW_H
