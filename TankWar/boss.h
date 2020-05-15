#ifndef BOSS_H
#define BOSS_H

#include "base.h"
#include "main.h"

class Boss: public Base
{
public:
    Boss();

    void display(QPainter& paint) override;
    void move() override;
    void beAttacked(int attack) override;
    void calSphere() override;
};

#endif // BOSS_H
