#include "missile.h"

Missile::Missile(const Tank& tank)
{
    dir = tank.dir;
    pos.setX(tank.pos.x() + 21);
    pos.setY(tank.pos.y() + 21);
    calSphere();

    step = tank.step + 10;
    attack = tank.attack;
    kind = tank.kind;
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


void Missile::move()
{

    switch(this->dir)
    {
    case UP:
        pos.setY(pos.y() - step);
        break;
    case DOWN:
        pos.setY(pos.y() + step);
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

    //与地图块碰撞
    for(int i = 0; i < ROW; ++i)
    {
        for(int j = 0; j < COL; ++j)
        {
            if(info.map->getCell(i,j) != NULL
                    && info.map->getCell(i,j)->is_penetration_of_missile() == false
                    && this->isBoom(info.map->getCell(i,j)))
            {

                info.map->getCell(i,j)->beAttacked(attack);

                setDisappear(true);

                qDebug("tank hit cell");

            }
        }
    }

    //碰撞边界
    if(this->rectSphere.left() < 0
            || this->rectSphere.right() > MAPWIDTH
            || this->rectSphere.bottom() > MAPHEIGHT
            || this->rectSphere.top() < 0)
    {
        qDebug("missile out");
        setDisappear(true);
    }


    //玩家导弹
    if(this->group == 0)
    {
        //玩家导弹撞到敌方坦克
        for(int i = 0; i < info.enemytanks.count(); ++i)
        {
            if(info.enemytanks.at(i) != NULL
                    && this->isBoom(info.enemytanks.at(i)))
            {

                info.enemytanks.at(i)->beAttacked(attack);

                setDisappear(true);
            }
        }

        //玩家导弹撞到敌方导弹
        for(int i = 0; i < info.enemytanks.count(); ++i)
        {
            if(info.enemytanks.at(i) != NULL
                    && this->isBoom(info.enemytanks.at(i)) == true)
            {
                setDisappear(true);
                info.enemytanks.at(i)->setDisappear(true);
            }
        }

    }


    //敌方导弹
    if(this->group == 1)
    {

        //敌方导弹碰撞到玩家坦克
        if(this->isBoom(info.player))
        {

            info.player->beAttacked(attack);
            setDisappear(true);

        }

        //敌方导弹碰撞到敌方坦克
        for(int i = 0; i < info.enemytanks.count(); ++i)
        {
            if(info.enemytanks.at(i) != NULL
                    && this->isBoom(info.enemytanks.at(i)))
            {
               setDisappear(true);
            }

        }

        //敌方导弹碰到我方导弹
        for(int i = 0; i < info.player->missilesOfTank.count(); ++i)
        {
            if(this->isBoom(info.player->missilesOfTank.at(i)) == true)
            {
                this->setDisappear(true);
                info.player->missilesOfTank.at(0)->setDisappear(true);
            }
        }
    }
}

void Missile::beAttacked(int attack)
{

}
