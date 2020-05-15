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


    //导弹是否与地图块碰撞

    for(int i = 0;i < ROW; ++i)
    {
        for(int j = 0; j < COL; ++j)
        {
            if(info.map->getCell(i,j) != NULL)
            {
                if(info.map->getCell(i,j)->is_penetration_of_missile() == false)
                {
                    if(isBoom(info.map->getCell(i,j)))
                    {
                        qDebug("hit cell");

                        info.map->getCell(i,j)->beAttacked(attack);

                        setDisappear(true);

                        if(this->kind == info.player->kind
                                && info.player->missileNum == 1)

                            info.player->setMissileNum();
                        }

                        for(int k = 0;k < info.enemytanks.count();++k)
                        {
                            if(this->kind == info.enemytanks.at(k)->kind
                                    && info.enemytanks.at(k)->missileNum == 1)
                            {
                                info.enemytanks.at(k)->setMissileNum();
                                break;
                            }
                        }
                    }
                }
            }
   }


    qDebug("missile cell-------");



    //击中敌方坦克
    for(int i = 0; i < info.enemytanks.count(); ++i)
    {

        if(info.enemytanks.at(i)
                && info.enemytanks.at(i)->group != this->group
                && isBoom(info.enemytanks.at(i)))
        {

            setDisappear(true);//导弹消失
            info.enemytanks.at(i)->beAttacked(attack);

            //玩家导弹
            if(info.player->missileNum == 1 && this->kind == info.player->kind)
            {
                info.player->setMissileNum();
            }


            //敌方导弹
            for(int k = 0; k < info.enemytanks.count();++k)
            {
                if(info.enemytanks.at(k)->missileNum == 1 && this->kind == info.enemytanks.at(k)->kind)
                {
                    info.enemytanks.at(k)->setMissileNum();
                    break;
                }
            }
            qDebug("hit tank!!!!!!!!");


        }
    }
    qDebug("missile tank-------");




    if(info.player->group != this->group
            && isBoom(info.player))
    {

        setDisappear(true);//导弹消失
        info.player->beAttacked(attack);

        if(info.player->missileNum == 1 && this->kind == info.player->kind)
        {
            info.player->setMissileNum();
        }

        for(int k = 0; k < info.enemytanks.count(); ++k)
        {
            if(info.enemytanks.at(k)->missileNum == 1 && this->kind == info.enemytanks.at(k)->kind)
            {
                info.enemytanks.at(k)->setMissileNum();
                break;
            }
        }
    }







    //击中玩家坦克
    if(this->group == 1)
    {
        for(int i = 0; i < info.enemytanks.count();++i)
        {
            if(info.enemytanks.at(i)
                    && this->isBoom(info.player))
            {
                this->setDisappear(true);
                info.player->beAttacked(this->attack);

                for(int k = 0; k < info.enemytanks.count();++k)
                {
                    if(info.enemytanks.at(k)->missileNum == 1
                            && this->kind == info.enemytanks.at(k)->kind)
                    {
                        info.enemytanks.at(k)->setMissileNum();
                        break;
                    }
                }
            }
        }
    }

    //导弹是否出界
    if(pos.x() < 0
            ||pos.x() > MAPWIDTH - 5
            ||pos.y() < 0
            ||pos.y() > MAPHEIGHT - 5)
    {

        setDisappear(true);//导弹消失

        if(info.player->missileNum == 1 && this->kind == info.player->kind)
        {
            info.player->setMissileNum();
        }

        for(int k = 0; k < info.enemytanks.count();++k)
        {
            if(info.enemytanks.at(k)->missileNum == 1 && this->kind == info.enemytanks.at(k)->kind)
            {
                info.enemytanks.at(k)->setMissileNum();
                break;
            }
        }

        qDebug("missile hit edge!!!!!!!!");
    }
    qDebug("missile edge------");



    //击中boss
    if(this->isBoom(info.boss))
     {

         //导弹消失
         setDisappear(true);

         info.boss->beAttacked(attack);
         info.boss->setDisappear(true);

         if(info.player->missileNum == 1 && this->kind == info.player->kind)
         {
             info.player->setMissileNum();
         }

         for(int k=0;k<info.enemytanks.count();++k)
         {
             if(info.enemytanks.at(k)->missileNum==1&&this->kind==info.enemytanks.at(k)->kind)
             {
                 info.enemytanks.at(k)->setMissileNum();
                 break;
             }
         }
     }

}

void Missile::beAttacked(int attack)
{

}
