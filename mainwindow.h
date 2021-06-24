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
    bool m_premiere_fois_start;
    int m_timer_window;
    QGraphicsSimpleTextItem *m_text_item;
    int m_num_score;
    QGraphicsSimpleTextItem *m_score;
    int m_num_vie;
    QGraphicsSimpleTextItem *m_vie;
    ennemi *Ennemi[15][2];
    Vaisseau *vaisseau_joueur;      // vaisseau
    Projectile *tir_joueur[5];     //projectiles (tirs du vaisseau)
    int sel_projectile = 0;     //selection du projectile
    bool game_over = false;
    Projectile *tir_ennemis;
    bool type;

};
#endif // MAINWINDOW_H
