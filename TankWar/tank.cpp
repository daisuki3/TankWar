#include "tank.h"

int Tank::steps[kindNum] = {12,12,12,12};
int Tank::lifes[kindNum] = {10000,100,200,300};
int Tank::attacks[kindNum] = {100,100,100,100};

Tank::Tank()
{

    pos.setX(4 * CELLWIDTH);
    pos.setY(12 * CELLHEIGHT);

    calSphere();

    group = 0;
    step = 12;
    kind = 0;
    isMove = false;
    isFire = false;
    dir = UP;
    disappear = false;
    life = lifes[kind];
    attack = attacks[kind];
    missileNum = 0;

}

Tank::Tank(int row, int col, Dir dir,int kind, int group)
{
    pos.setX(row * CELLWIDTH);
    pos.setY(col * CELLHEIGHT);

    calSphere();
    this->group = group;
    this->dir = dir;
    this->kind = kind;

    step = steps[kind];
    disappear = false;
    isFire = false;
    life = lifes[kind];
    attack = attacks[kind];
    missileNum = 0;

}

void Tank::calSphere()
{
    rectSphere.setRect(pos.x(), pos.y(), CELLWIDTH, CELLHEIGHT);
}

void Tank::display(QPainter &paint)
{

}


