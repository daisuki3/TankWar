#ifndef CELL_H
#define CELL_H

#include "base.h"
#include "main.h"


const int BOSS = 0;
const int WALL = 1;
const int STEEL = 2;
const int WATER = 3;
const int GROUND = 4;

const int cellNum = 5;
//老大 墙 铁墙 水 地

class Cell:public Base
{

public:
    Cell();
    Cell(int row = 0, int col = 0, int cur_kind = 4);

    int kind;//老大 墙 铁墙 水 地

    static int lifes[cellNum];
    static bool penetrations_of_tank[cellNum];
    static bool penetrations_of_missile[cellNum];

    bool is_penetration_of_tank();
    bool is_penetration_of_missile();

    void display(QPainter &paint) override;

    void move() override;

    void beAttacked(int attack) override;

    void calSphere() override;

};

#endif // CELL_H
