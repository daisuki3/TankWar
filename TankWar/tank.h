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

        bool isMove;
        bool isFire;

public:

    static int steps[kindNum];
    static int lifes[kindNum];
    static int attacks[kindNum];

    Tank();
    Tank(int, int, Dir = UP, int = 0, int = 0);

    friend class Missile;
    QList<Missile*> missilesOfTank;

    virtual void display(QPainter& paint) override;
    virtual void move() override;
    virtual void beAttacked(int attack) override;
    virtual void calSphere() override;

    void setDir(Dir dir);

    void fire();
    bool getIsFire() const;
    void startFire();
    void stopFire();

    void moveForJudge();
    void startMove();
    void stopMove();

    bool isToCollision();

    int getKind() const;
    int getGroup() const;

};

#endif // TANK_H
