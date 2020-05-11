#include "cell.h"

#include <QImage>

int Cell::lifes[cellNum]={1,1,10000,0,0};
//老王=1 墙=2 铁墙=10000 水=0 地=0
bool Cell::penetrations_of_tank[cellNum] = {false,false,false,false,true};
bool Cell::penetrations_of_missile[cellNum] = {false,false,false,true,true};

Cell::Cell()
{

}

Cell::Cell(int row,int col,int cur_kind)
{

    this->kind = cur_kind;

    this->pos.setX(row * CELLWIDTH);
    this->pos.setY(col * CELLHEIGHT);
    this->calSphere();
    this->disappear = false;
    this->life = lifes[this->kind];

}

void Cell::display(QPainter &paint)
{

    if(this->isDisappear() == true)
        return;

    switch(this->kind)
    {
    case 0:
        paint.drawImage(rectSphere, info.cellImages[0]);
        break;
    case 1:
        paint.drawImage(rectSphere, info.cellImages[1]);
        break;
    case 2:
        paint.drawImage(rectSphere, info.cellImages[2]);
        break;
    case 3:
        paint.drawImage(rectSphere, info.cellImages[3]);
        break;
    case 4:
        break;
    default:
        break;
    }


}

void Cell::move()
{
    //can't move, do nothing
    return;
}

void Cell::calSphere()
{
    this->rectSphere.setRect(pos.x(), pos.y(),
                               CELLWIDTH,CELLHEIGHT);
}

void Cell::beAttacked(int attack)
{
    if(life > 0)
        life -= attack;

    if(life <= 0)
    {
        this->disappear = true;
        life = 0;
    }

}

bool Cell::is_penetration_of_tank()
{
    return penetrations_of_tank[kind];
}

bool Cell::is_penetration_of_missile()
{
    return penetrations_of_missile[kind];
}
