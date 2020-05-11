#ifndef BOSS_H
#define BOSS_H

#include "base.h"
#include "main.h"

class Boss: public Base
{
public:
    Boss();

    virtual void display(QPainter& paint) override;
    virtual void move() override;
    virtual void beAttacked(int attack) override;

protected:
    virtual void calSphere() override;
};

#endif // BOSS_H
