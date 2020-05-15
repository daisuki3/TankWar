#include "boss.h"

Boss::Boss()
{

    setDisappear(false);

    this->pos.setX(6 * CELLWIDTH);
    this->pos.setY(12 * CELLHEIGHT);
    this->life = 1;

    this->calSphere();
}

void Boss::display(QPainter &paint)
{
    if(isDisappear() == false)
        paint.drawImage(rectSphere, info.bossPic);
}

void Boss::calSphere()
{
    if(isDisappear() == false)
        rectSphere.setRect(pos.x(), pos.y(), CELLWIDTH, CELLHEIGHT);
}

void Boss::beAttacked(int attack)
{
    setDisappear(true);

    return ;
}

void Boss::move()
{
//do nothing
}
