#ifndef MAIN
#define MAIN

#define ROW 13//13行13列
#define COL 13

#define PIXWIDTH 60//图片尺寸
#define PIXHEIGHT 60

#define CELLWIDTH 60//分块尺寸
#define CELLHEIGHT 60

#define MAPWIDTH 60 * 13//全地图尺寸
#define MAPHEIGHT 60 * 13

#define MISSILEWIDTH 17
#define MISSILEHEIGHT 17

class Cell;
class Map;
class Tank;
class Base;
class Missile;
class Boss;

#include<QList>
#include<QImage>

struct INFO
{
    Map *map;
    Tank *player;
    Boss *boss;
    //npc坦克
    QList<Tank*> enemytanks;

    QList<Missile*> playerMissiles;

    //地图块图片
    QImage cellImages[3];

    //坦克上下左右的图片
    QImage tankImages[16];

    QImage missilePic;
    QImage bossPic;
    QImage boomPic;

    //玩家总得分
    int score;

    //三种坦克数
    int enemyTank1Num;
    int enemyTank2Num;
    int enemyTank3Num;

    //已击毁敌方坦克总数
    int enemyTankDestroyed;

    //int playerTanksNum;
};

extern INFO info;

#endif // MAIN_H
