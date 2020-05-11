#ifndef MISSILE_H
#define MISSILE_H

#include "base.h"
#include "main.h"
#include "tank.h"
#include "boss.h"

class Missile: public Base
{
private:
    int group;
public:

    Missile(const Tank& tank);

    friend class Tank;

    virtual void display(QPainter& paint) override;
    virtual void move() override;
    virtual void beAttacked(int attack) override;
    virtual void calSphere() override;

    int getGroup() const;
};

#endif // MISSILE_H
