#ifndef TANK_H
#define TANK_H

#include "base.h"
#include "main.h"
#include "map.h"
#include "missile.h"

const int kindNum = 4;

class Tank: public Base
{
private:
        int kind;
        // 0玩家 1：敌方坦克1 2：敌方坦克2 3：敌方坦克3

        int group;
        //玩家0 敌方1

        //int missileNum;

        bool isMove;
        bool isFire;

public:

    static int steps[kindNum];
    static int lifes[kindNum];
    static int attacks[kindNum];

    Tank();
    Tank(int row, int col, Dir = UP, int kind = 0);

    friend class Missile;
    friend class Cell;

    QList<Missile*> missilesOfTank;

    void display(QPainter& paint) override;
    void move() override;
    void beAttacked(int attack) override;
    void calSphere() override;

    void setDir(Dir dir);
    void setMissileNum();

    void fire();
    bool getIsFire() const;
    void startFire();
    void stopFire();

    void moveForJudge();
    void startMove();
    void stopMove();

    bool isToCollision();

};

#endif // TANK_H
