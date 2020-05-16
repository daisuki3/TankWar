#include "boss.h"

Boss::Boss()
{

    this->setDisappear(false);

    this->calSphere();
}

void Boss::display(QPainter &paint)
{

}

void Boss::calSphere()
{
    if(isDisappear() == false)
        rectSphere.setRect(pos.x(), pos.y(), CELLWIDTH, CELLHEIGHT);
}

void Boss::beAttacked(int attack)
{
    qDebug("boss boom");
    this->setDisappear(true);

    return;
}

void Boss::move()
{
//do nothing
}
