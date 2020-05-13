#include "missile.h"

Missile::Missile(const Tank& tank)
{
    dir = tank.dir;
    pos.setX(tank.pos.x()+21);
    pos.setY(tank.pos.y()+21);
    calSphere();

    step = tank.step + 10;
    attack = tank.attack;
    group = tank.group;

    setDisappear(false);
}

void Missile::display(QPainter &paint)
{
    if(this->isDisappear())
        return;

    paint.drawImage(rectSphere, info.missilePic);
}

void Missile::calSphere()
{
     rectSphere.setRect(pos.x(),pos.y(), MISSILEWIDTH,
                        MISSILEHEIGHT);
}

int Missile::getGroup() const
{
    return group;
}

void Missile::move()
{

    switch(this->dir)
    {
    case UP:
        pos.setY(pos.y() + step);
        break;
    case DOWN:
        pos.setY(pos.y() - step);
        break;
    case LEFT:
        pos.setX(pos.x() - step);
        break;
    case RIGHT:
        pos.setX(pos.x() + step);
        break;
    }

    calSphere();
    qDebug("before missile boom");


    //导弹是否与地图块碰撞
    /*
    for(int i=0;i<ROW;++i)
    {
        for(int j=0;j<COL;++j)
        {
            if(info.map->getCell(i,j) != NULL)
            {
                if(info.map->getCell(i,j)->is_penetration_of_missile() == false)
                {
                    if(isBoom(info.map->getCell(i,j)))
                    {
                        qDebug("墙被子弹射击了");

                        info.map->getCell(i,j)->beAttacked(attack);

                        setDisappear(true);

                    }
                }
            }
        }
    }
    */

    //击中敌方坦克


    //击中玩家坦克


    //导弹是否出界

    /*
    if(pos.x() < 0
            ||pos.x() > MAPWIDTH - 5
            ||pos.y() < 0
            ||pos.y() > MAPHEIGHT - 5)
    {

        setDisappear(true);//导弹消失


        qDebug("missile hit edge!!!!!!!!");
    }
    */


    //击中boss


}

void Missile::beAttacked(int attack)
{

}
