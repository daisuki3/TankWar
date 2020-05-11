#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main.h"
#include "map.h"
#include "boss.h"
#include "tank.h"

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include <QLabel>

#define TIME_INTERVAL 60


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum GameStatus{gaming,pause,over};

    void initGame();

    void loadCell();

    void isAllDisappeared() const;

    void missileMeet();

    void isOver();

    GameStatus getGameStatus() const;

    void showPlayerInfo();

private slots:
  void paintEvent(QPaintEvent* event);

  void keyPressEvent(QKeyEvent* event);

  void keyReleaseEvent(QKeyEvent* event);

  void timeFun();

  void showLunchInfo();

  void showTips();

  void showPauseInfo();

  void showLoss();

  void showEnd();

private:
    Ui::MainWindow *ui;

    void setGameStatus(GameStatus status);
    GameStatus m_status;

    Map m_map;

    QTimer* timer;
    QPainter paint;

    QLabel* score;

    QLabel* tankNum;

    QLabel* tankLife;

    QLabel* gamepause;

};

#endif // MAINWINDOW_H
