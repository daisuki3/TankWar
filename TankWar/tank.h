#ifndef TANK_H
#define TANK_H

#include "base.h"
#include "main.h"
#include "map.h"


const int kindNum = 4;

class Tank: public Base
{
private:
        int kind;
        int group;

        bool isMove;
        bool isFire;

        int missileNum;

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

    void setAttack();
    void setDir(Dir dir);

    void fire();
    bool getIsFire() const;

    void startFire();
    void stopFire();


    bool isToCollision();

//    void setMissileNum(int num);
  //  int getMissileNum() const;

    int getKind() const;
    int getGroup() const;

};

#endif // TANK_H
