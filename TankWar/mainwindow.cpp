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
    setWindowIcon(QIcon(":/new/prefix1/pixs/p1tankD.png"));


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
    //载入信息

    status = gaming;

    info.map = new Map();
    info.player = new Tank();
    info.boss = new Boss();

    info.enemyTank1Num = 1;
    info.enemyTank2Num = 1;
    info.enemyTank3Num = 1;

    info.enemyTankDestroyed = 0;


    /*
     * 加入敌方坦克
     */

    //初始化图片
    info.cellImages[0].load(":/new/prefix1/pixs/1_1.png");
    info.cellImages[1].load(":/new/prefix1/pixs/2_1.png");
    info.cellImages[2].load(":/new/prefix1/pixs/3.png");
    info.cellImages[3].load(":/new/prefix1/pixs/4.png");
    info.cellImages[4].load(":/new/prefix1/pixs/5.png");

    info.tankImages[0].load(":/new/prefix1/pixs/p1tankU.png");
    info.tankImages[1].load(":/new/prefix1/pixs/p1tankD.png");
    info.tankImages[2].load(":/new/prefix1/pixs/p1tankL.png");
    info.tankImages[3].load(":/new/prefix1/pixs/p1tankR.png");

    info.tankImages[4].load(":/new/prefix1/pixs/enemy1U.png");
    info.tankImages[5].load(":/new/prefix1/pixs/enemy1D.png");
    info.tankImages[6].load(":/new/prefix1/pixs/enemy1L.png");
    info.tankImages[7].load(":/new/prefix1/pixs/enemy1R.png");

    info.tankImages[8].load(":/new/prefix1/pixs/enemy2U.png");
    info.tankImages[9].load(":/new/prefix1/pixs/enemy2D.png");
    info.tankImages[10].load(":/new/prefix1/pixs/enemy2L.png");
    info.tankImages[11].load(":/new/prefix1/pixs/enemy2R.png");

    info.tankImages[12].load(":/new/prefix1/pixs/enemy3U.png");
    info.tankImages[13].load(":/new/prefix1/pixs/enemy3D.png");
    info.tankImages[14].load(":/new/prefix1/pixs/enemy3L.png");
    info.tankImages[15].load(":/new/prefix1/pixs/enemy3R.png");

    info.missilePic.load(":/new/prefix1/pixs/tankMissile.png");
    info.bossPic.load(":/new/prefix1/pixs/boss.png");

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
                                  "\n\n  J 射击"
                                  "\n\n  P 暂停"
                                  "\n\n  G 恢复"));
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

void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    setFixedSize(MAPWIDTH + 160, MAPHEIGHT);

    paint.begin(this);

    info.map->display(paint);
    info.boss->display(paint);
    info.player->display(paint);

    for(int i = 0; i < info.enemytanks.count(); ++i)
    {
        info.enemytanks.at(i)->display(paint);
    }

    paint.end();

}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    Q_UNUSED(event);

    if(event->key() == Qt::Key_P)
    {
        status = pause;

        info.player->stopMove();

        for(int i = 0; i < info.enemytanks.count(); ++i)
            info.enemytanks.at(i)->stopMove();

        showPauseInfo();
    }
    else if(event->key()==Qt::Key_G)
        {
            status=gaming;
        }

    if(status == gaming)
    {
            if(event->key()==Qt::Key_W)
            {
                info.player->setDir(UP);
                info.player->startMove();
            }
            else if(event->key()==Qt::Key_S)
            {
                info.player->setDir(DOWN);
                info.player->startMove();
            }
            else if(event->key()==Qt::Key_A)
            {
                info.player->setDir(LEFT);
                info.player->startMove();
            }
            else if(event->key()==Qt::Key_D)
            {
                info.player->setDir(RIGHT);
                info.player->startMove();
            }
            else if(event->key()==Qt::Key_J)
            {
                info.player->startFire();
            }
    }

    update();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_J)
     {
         info.player->stopFire();
     }
     else
     {
         info.player->stopMove();
     }

}


void MainWindow::timeFun()
{
    if(status!=gaming)
        return;

    Dir tmpDir;
    int tmp;



    //获取当前时间
    QTime time = QTime::currentTime();
    //设置随机数种子
    qsrand(time.msec()+time.second()*100000);

    //敌人坦克控制
    for(int i=0;i<info.enemytanks.count();++i)
    {

        if(qrand()%5==0)
        {
            info.enemytanks.at(i)->startMove();
            info.enemytanks.at(i)->startFire();
        }

        if(qrand()%10==0)
        {
            info.enemytanks.at(i)->stopMove();
        }

        if(qrand()%5==0)
        {
            info.enemytanks.at(i)->stopFire();
        }

        if(qrand()%10==0)
        {
            tmp=qrand()%9;
            switch(tmp)
            {
            case 0:
                tmpDir=UP;
                break;
            case 1:
                tmpDir=DOWN;
                break;
            case 2:
                tmpDir=LEFT;
                break;
            case 3:
                tmpDir=RIGHT;
                break;
            case 4:
                tmpDir=DOWN;
                break;
            case 5:
                tmpDir=DOWN;
                break;
            case 6:
                tmpDir=DOWN;
                break;
            case 7:
                tmpDir=LEFT;
                break;
            case 8:
                tmpDir=RIGHT;
                break;
            default:
                break;
            }
            info.enemytanks.at(i)->setDir(tmpDir);
         }

    }
    //end

    info.player->move();
    info.player->fire();



    for(int i=0;i<info.enemytanks.count();++i)
    {
        info.enemytanks.at(i)->move();
        info.enemytanks.at(i)->fire();
    }

}
