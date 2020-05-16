#include "mainwindow.h"

#include <QRect>
#include <QPen>
#include <QTime>
#include <QDebug>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    Sleep(1000);



    showLunchInfo();
    showTips();

    setWindowTitle("Tank War");
    setWindowIcon(QIcon(":/new/prefix1/pixs/p1tankD.png"));


    QFont font;
    font.setPointSize(32);
    paint.setFont(font);
    paint.setPen(QColor(255,0,0));


    score1 = new QLabel(this);
    score2 = new QLabel(this);

    tankLife1 = new QLabel(this);
    tankLife2 = new QLabel(this);

    gamepause = new QLabel(this);

    //info.playerTanksNum = 1;
    initGame();
}


MainWindow::~MainWindow()
{

    timer->stop();
    delete  timer;
}


void MainWindow::initGame()
{
    move(600,50);
    //载入信息

    status = gaming;

    info.map = new Map();
    info.player = new Tank();
    info.boss = new Boss();

    info.enemyTank1Num = 1;
    info.enemyTank2Num = 1;
    info.enemyTank3Num = 1;

    Tank* tmp = new Tank(0,0,DOWN,1);
    info.enemytanks.append(tmp);

    tmp = new Tank(6,6,DOWN,2);
    info.enemytanks.append(tmp);

    tmp = new Tank(2,12,DOWN,3);
    info.enemytanks.append(tmp);



    info.enemyTankDestroyed = 0;



    /*
     * 初始化图片
     * 1 老王
     * 2 墙
     * 3 铁墙
     * 4 水
     * 5 地
     * */

    //墙
    info.cellImages[0].load(":/new/prefix1/1_1.png");
    //铁墙
    info.cellImages[1].load(":/new/prefix1/2_1.png");
    //水
    info.cellImages[2].load(":/new/prefix1/4.png");
    //地

    info.tankImages[0].load(":/new/prefix1/p1tankU.png");
    info.tankImages[1].load(":/new/prefix1/p1tankD.png");
    info.tankImages[2].load(":/new/prefix1/p1tankL.png");
    info.tankImages[3].load(":/new/prefix1/p1tankR.png");

    info.tankImages[4].load(":/new/prefix1/enemy1U.png");
    info.tankImages[5].load(":/new/prefix1/enemy1D.png");
    info.tankImages[6].load(":/new/prefix1/enemy1L.png");
    info.tankImages[7].load(":/new/prefix1/enemy1R.png");

    info.tankImages[8].load(":/new/prefix1/enemy2U.png");
    info.tankImages[9].load(":/new/prefix1/enemy2D.png");
    info.tankImages[10].load(":/new/prefix1/enemy2L.png");
    info.tankImages[11].load(":/new/prefix1/enemy2R.png");

    info.tankImages[12].load(":/new/prefix1/enemy3U.png");
    info.tankImages[13].load(":/new/prefix1/enemy3D.png");
    info.tankImages[14].load(":/new/prefix1/enemy3L.png");
    info.tankImages[15].load(":/new/prefix1/enemy3R.png");

    info.missilePic.load(":/new/prefix1/tankMissile.png");
    info.bossPic.load(":/new/prefix1/boss.png");

    loadCell();

    status = gaming;

    timer = new QTimer(this);
    timer->setInterval(TIME_INTERVAL);
    connect(timer, SIGNAL(timeout()),
            this,SLOT(timeFun()));

    timer->start();

}


void MainWindow::loadCell()
{
    info.map->loadMap();
}


void MainWindow::showPlayerInfo()
{

    score1->setText(tr("score:"));
    QRect r1(790,90,80,20);
    score1->setGeometry(r1);

    QString str1;
    score2->setText(str1.setNum(info.score));
    QRect r2(860,110,80,20);
    score2->setGeometry(r2);




    tankLife1->setText(tr("life:"));
    QRect r3(790,650,100,20);
    tankLife1->setGeometry(r3);

    QString str2;
    tankLife2->setText(str2.setNum(info.player->life));
    QRect r4(880,670,80,20);
    tankLife2->setGeometry(r4);

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
                                  "\n\n  J 射击"
                                  "\n\n  P 暂停"
                                  "\n\n  G 恢复"));
}


void MainWindow::showPauseInfo()
{
    gamepause->setText(tr("暂停!"));
    gamepause->setGeometry(800,500,70,20);
}


void MainWindow::showResume()
{
    gamepause->setText(tr("游戏中"));
    gamepause->setGeometry(800,500,70,20);
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

    this->showPlayerInfo();

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
            showResume();
        }


    if(status == gaming)
    {
            if(event->key() == Qt::Key_W)
            {
                info.player->setDir(UP);
                info.player->startMove();
            }
            else if(event->key() == Qt::Key_S)
            {
                info.player->setDir(DOWN);
                info.player->startMove();
            }
            else if(event->key() == Qt::Key_A)
            {
                info.player->setDir(LEFT);
                info.player->startMove();
            }
            else if(event->key() == Qt::Key_D)
            {
                info.player->setDir(RIGHT);
                info.player->startMove();
            }
            else if(event->key() == Qt::Key_J)
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
    if(status != gaming)
        return;

    Dir tmpDir;
    int tmp;


    //获取当前时间
    QTime time = QTime::currentTime();
    //设置随机数种子
    qsrand(time.msec()+time.second()*100000);

    //敌人坦克控制
    for(int i = 0; i < info.enemytanks.count(); ++i)
    {

        if(qrand()%2 == 0)
        {
            qDebug("%d",qrand());
            qDebug("enemy move and fire");

            info.enemytanks.at(i)->startMove();
           // info.enemytanks.at(i)->startFire();
        }

        if(qrand()%10==0)
        {
            info.enemytanks.at(i)->stopMove();
        }

        if(qrand()%5==0)
        {
            //info.enemytanks.at(i)->stopFire();
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

   // missileMeet();


    if(isEnemyAllDisappeared())
    {
        status = pause;

        timer->stop();

        showEnd();

        this->close();
    }


    this->isOver();
    qDebug("time out");
    update();
}


bool MainWindow::isEnemyAllDisappeared() const
{
    for(int i = 0; i < info.enemytanks.count(); ++i)
    {
        if(info.enemytanks.at(i)->isDisappear() == false)
            return false;
    }

    return true;
}

/*
void MainWindow::missileMeet()
{
    int missileNum = info.player->missilesOfTank.count();

      if(missileNum == 1)
      {
          for(int i = 0; i < info.enemytanks.count(); ++i)
                  {
                      if(info.enemytanks.at(i)->getIsFire() == true
                              && info.player->missilesOfTank.at(0)->isBoom(info.enemytanks.at(i)->missilesOfTank.at(0)))
                      {
                          //玩家导弹消失
                          info.player->missilesOfTank.at(0)->setDisappear(true);

                          //敌方导弹消失
                          info.enemytanks.at(i)->missilesOfTank.at(0)->setDisappear(true);

                          //恢复导弹数
                          info.player->setMissileNum();
                          info.enemytanks.at(i)->setMissileNum();

                          break;
                      }

                  }
      }
}
*/

void MainWindow::isOver()
{
    if(info.boss->isDisappear()
            || info.player->isDisappear())
    {
        status=pause;
        timer->stop();
        showLoss();

        //删除敌方坦克
        for(int i = 0; i < info.enemytanks.count();++i)
        {
            bool tmp=true;
            info.enemytanks.at(i)->setDisappear(tmp);
            delete info.enemytanks.at(i);
            info.enemytanks.removeAt(i);
        }

        //删除玩家坦克
        info.player=NULL;


        for(int i=0;i<ROW;++i)
        {
            for(int j=0;j<COL;++j)
            {
                *info.map->getCell(i,j)=NULL;
                delete info.map->getCell(i,j);
            }
        }

        this->close();
    }
}
