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



                        for(int k = 0;k < glb.enemytanks.count(); ++k)
                        {
                            if(this->kind==glb.enemytanks.at(k)->kind&&glb.enemytanks.at(k)->getMissileNum()==1)
                            {
                                glb.enemytanks.at(k)->setMissileNum();
                                break;
                            }
                        }


                    }
                }
            }
        }
    }
    qDebug("missile 1-------");



    //击中敌方坦克
    for(int i=0;i<glb.enemytanks.count();++i)
    {
        if(glb.enemytanks.at(i)
                &&glb.enemytanks.at(i)->group!=this->group
                &&isCollision(*glb.enemytanks.at(i)))
        {
            bool tmp=true;
            setDisappear(tmp);//导弹消失
            glb.enemytanks.at(i)->beAttacked(attack);

            if(glb.player->getMissileNum()==1&&this->kind==glb.player->kind)
            {
                glb.player->setMissileNum();
            }

            for(int k=0;k<glb.enemytanks.count();++k)
            {
                if(glb.enemytanks.at(k)->getMissileNum()==1&&this->kind==glb.enemytanks.at(k)->kind)
                {
                    glb.enemytanks.at(k)->setMissileNum();
                    break;
                }
            }
            qDebug("missile hit tank!!!!!!!!");


        }
    }
    qDebug("missile 2-------");

    if(glb.player->group!=this->group
            &&isCollision(*glb.player))
    {
        bool tmp=true;
        setDisappear(tmp);//导弹消失
        glb.player->beAttacked(attack);

        if(glb.player->getMissileNum()==1&&this->kind==glb.player->kind)
        {
            glb.player->setMissileNum();
        }

        for(int k=0;k<glb.enemytanks.count();++k)
        {
            if(glb.enemytanks.at(k)->getMissileNum()==1&&this->kind==glb.enemytanks.at(k)->kind)
            {
                glb.enemytanks.at(k)->setMissileNum();
                break;
            }
        }
    }

    //敌方导弹是否击中玩家坦克
    if(this->group==1)
    {
        for(int i=0;i<glb.enemytanks.count();++i)
        {
            if(glb.enemytanks.at(i)&&this->isCollision(*glb.player))
            {
                bool tmp=true;
                this->setDisappear(tmp);
                glb.player->beAttacked(this->attack);

                for(int k=0;k<glb.enemytanks.count();++k)
                {
                    if(glb.enemytanks.at(k)->getMissileNum()==1&&this->kind==glb.enemytanks.at(k)->kind)
                    {
                        glb.enemytanks.at(k)->setMissileNum();
                        break;
                    }
                }
            }
        }
    }


    //导弹是否出界
    if(pos.x()<0
            ||pos.x()>Width-5
            ||pos.y()<0
            ||pos.y()>Height-5)
    {
        bool tmp=true;
        setDisappear(tmp);//导弹消失

        if(glb.player->getMissileNum()==1&&this->kind==glb.player->kind)
        {
            glb.player->setMissileNum();
        }

        for(int k=0;k<glb.enemytanks.count();++k)
        {
            if(glb.enemytanks.at(k)->getMissileNum()==1&&this->kind==glb.enemytanks.at(k)->kind)
            {
                glb.enemytanks.at(k)->setMissileNum();
                break;
            }
        }


        qDebug("missile hit edge!!!!!!!!");
    }
    qDebug("missile 3------");


    //导弹是否击中boss
    if(this->isCollision1(*glb.boss))
    {
        bool tmp=true;
        //导弹消失
        setDisappear(tmp);

        glb.boss->beAttacked(attack);
        glb.boss->setDisappear(tmp);

        if(glb.player->getMissileNum()==1&&this->kind==glb.player->kind)
        {
            glb.player->setMissileNum();
        }

        for(int k=0;k<glb.enemytanks.count();++k)
        {
            if(glb.enemytanks.at(k)->getMissileNum()==1&&this->kind==glb.enemytanks.at(k)->kind)
            {
                glb.enemytanks.at(k)->setMissileNum();
                break;
            }
        }
    }


}

void Missile::beAttacked(int attack)
{

}
