#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include <QRect>
#include <QPen>
#include <QTime>
#include <QDebug>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{

    showLunchInfo();
    showTips();

    setWindowTitle("Tank War");
    setWindowIcon(QIcon(":/new/icon/pixs/p1tankD.png"));

    QFont font;
    font.setPointSize(32);
    paint.setFont(font);
    paint.setPen(QColor(255,0,0));

    score = new QLabel(this);
    tankNum = new QLabel(this);
    tankLife = new QLabel(this);
    gamepause = new QLabel(this);

    initGame();

}

MainWindow::~MainWindow()
{
    //delete ui;

    timer->stop();
    delete  timer;
}

void MainWindow::initGame()
{
    m_status = gaming;

    info.map = new Map();

    info.enemyTank1Num = 1;
    info.enemyTank2Num = 1;
    info.enemyTank3Num = 1;

    info.enemyTankDestroyed = 0;

    info.player = new Tank();
    info.boss = new Boss();

    /*
     * 加入敌方坦克
     */

    //初始化图片
    info.cellImages[0].load(":pixs/1_1.png");
    info.cellImages[1].load(":/new/icon/pixs/2_1.png");
    info.cellImages[2].load(":/new/icon/pixs/3.png");
    info.cellImages[3].load(":/new/icon/pixs/4.png");
    info.cellImages[4].load(":/new/icon/pixs/5.png");

    info.playerTankImage[0].load(":/new/icon/pixs/p1tankU.png");
    info.playerTankImage[1].load(":/new/icon/pixs/p1tankD.png");
    info.playerTankImage[2].load(":/new/icon/pixs/p1tankL.png");
    info.playerTankImage[3].load(":/new/icon/pixs/p1tankR.png");

    info.enemyTank1Image[0].load(":/new/icon/pixs/enemy1U.png");
    info.enemyTank1Image[1].load(":/new/icon/pixs/enemy1D.png");
    info.enemyTank1Image[2].load(":/new/icon/pixs/enemy1L.png");
    info.enemyTank1Image[3].load(":/new/icon/pixs/enemy1R.png");

    info.enemyTank2Image[0].load(":/new/icon/pixs/enemy2U.png");
    info.enemyTank2Image[1].load(":/new/icon/pixs/enemy2D.png");
    info.enemyTank2Image[2].load(":/new/icon/pixs/enemy2L.png");
    info.enemyTank2Image[3].load(":/new/icon/pixs/enemy2R.png");

    info.enemyTank3Image[0].load(":/new/icon/pixs/enemy3U.png");
    info.enemyTank3Image[1].load(":/new/icon/pixs/enemy3D.png");
    info.enemyTank3Image[2].load(":/new/icon/pixs/enemy3L.png");
    info.enemyTank3Image[3].load(":/new/icon/pixs/enemy3R.png");

    info.missilePic.load(":/new/icon/pixs/tankMissile.png");
    info.bossPic.load(":/new/icon/pixs/boss.png");

    timer = new QTimer(this);

    timer->setInterval(TIME_INTERVAL);
    connect(timer, SIGNAL(timeout()),
            this,SLOT(timeFun()));

    timer->start();

}

void MainWindow::showLunchInfo()
{
    setGeometry(880, 350, 200, 150);
    QMessageBox::information(this, tr("版本信息")
                             ,tr("Tank War v1.0"));

    return;
}

void MainWindow::showTips()
{
    setGeometry(880, 350, 200, 150);
    QMessageBox::information(this,tr("操作说明"),
                                 tr("WASD控制方向"
                                  "\n"
                                  "\n\n    j    设计"
                                  "\n\n    p    暂停"
                                  "\n\n    g    Resume"));
}

void MainWindow::showPauseInfo()
{
    gamepause->setText(tr("暂停!"));
    gamepause->setGeometry(865,755,70,20);
}

void MainWindow::showLoss()
{
    setGeometry(605,83,200,150);

    QMessageBox::information(this,tr("Tank War"),
                                   tr("游戏结束，你输了"));
}

void MainWindow::showEnd()
{
    setGeometry(605,83,200,150);
    QMessageBox::information(this,tr("Tank War"),
                                   tr("恭喜!"
                                      "\n你赢了!"));
    return;
}




