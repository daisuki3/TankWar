#ifndef CELL_H
#define CELL_H

#include "base.h"
#include "main.h"


const int BOSS = 0;
const int WALL = 1;
const int STELL = 2;
const int WATER = 3;
const int GROUND = 4;

const int cellNum = 5;
//老大 墙 铁墙 水 地

class Cell:public Base
{

public:
    Cell();
    Cell(int row = 0, int col = 0, int cur_kind = GROUND);

    int kind;//老大 墙 铁墙 水 地

    static int lifes[cellNum];
    static bool penetrations_of_tank[cellNum];
    static bool penetrations_of_missile[cellNum];

    bool is_penetration_of_tank();
    bool is_penetration_of_missile();

    virtual void display(QPainter &paint) override;

    virtual void move() override;

    virtual void beAttacked(int attack) override;

    virtual void calSphere() override;

};

#endif // CELL_H
