#include "boss.h"

Boss::Boss()
{
    bool dis = false;

    setDisappear(dis);

    this->pos.setX(6 * CELLWIDTH);
    this->pos.setY(12 * CELLHEIGHT);

    this->calSphere();
}

void Boss::display(QPainter &paint)
{
    if(isDisappear() == false)
        paint.drawImage(rectSphere, info.bossPic);
}

void Boss::calSphere()
{
    rectSphere.setRect(pos.x(), pos.y(), CELLWIDTH, CELLHEIGHT);
}

void Boss::beAttacked(int attack)
{
    setDisappear(false);

    return ;
}
