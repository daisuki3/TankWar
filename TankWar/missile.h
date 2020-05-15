#ifndef MISSILE_H
#define MISSILE_H

#include "base.h"
#include "main.h"
#include "tank.h"
#include "boss.h"

class Missile: public Base
{
public:

    Missile(const Tank& tank);

    friend class Tank;

    void display(QPainter& paint) override;
    void move() override;
    void beAttacked(int attack) override;
    void calSphere() override;

    int kind;
    int group;
};

#endif // MISSILE_H
