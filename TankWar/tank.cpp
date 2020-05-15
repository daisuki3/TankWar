#include "tank.h"

int Tank::steps[kindNum] = {12,12,12,12};
int Tank::lifes[kindNum] = {500,100,200,300};
int Tank::attacks[kindNum] = {100,100,100,100};
        // 0玩家 1：敌方坦克1 2：敌方坦克2 3：敌方坦克3
//玩家坦克
Tank::Tank()
{

    pos.setX(4 * CELLWIDTH);
    pos.setY(12 * CELLHEIGHT);

    calSphere();

    step = 12;
    kind = 0;
    dir = UP;
    missileNum = 0;

    isMove = false;
    isFire = false;
    disappear = false;

    life = lifes[kind];
    attack = attacks[kind];

}

//敌方坦克
Tank::Tank(int row, int col, Dir dir,int kind)
{
    pos.setX(row * CELLWIDTH);
    pos.setY(col * CELLHEIGHT);

    calSphere();

    this->dir = dir;
    this->kind = kind;
    this->missileNum = 0;

    disappear = false;
    isFire = false;
    step = steps[kind];
    life = lifes[kind];
    attack = attacks[kind];

}

void Tank::calSphere()
{
    rectSphere.setRect(pos.x(), pos.y(), CELLWIDTH, CELLHEIGHT);
}

void Tank::display(QPainter &paint)
{
    //绘制坦克发射的子弹
    for(int i = 0; i < missilesOfTank.count(); ++i)
    {
        if(missilesOfTank.at(i)->disappear == false)
            missilesOfTank.at(i)->display(paint);
        else
        {
            delete missilesOfTank.at(i);
            missilesOfTank.removeAt(i);
            i--;
        }
    }

    //绘制坦克
    if(disappear == true)
        return;

    switch (dir)
    {
    case UP:
        paint.drawImage(rectSphere,info.tankImages[kind * 4]);
        break;
    case DOWN:
        paint.drawImage(rectSphere,info.tankImages[kind * 4 + 1]);
        break;
    case LEFT:
        paint.drawImage(rectSphere,info.tankImages[kind * 4 + 2]);
        break;
    case RIGHT:
        paint.drawImage(rectSphere,info.tankImages[kind * 4 + 3]);
        break;
    }
}


void Tank::setDir(Dir dir)
{
    this->dir = dir;
}


void Tank::setMissileNum()
{
    missileNum = 0;
}


void Tank::move()
{
    //控制坦克发射的子弹的移动
    for(int i = 0;i < missilesOfTank.count(); i++)
        missilesOfTank.at(i)->move();

    //控制坦克的移动
    if(disappear == true)
        return;

    if(isToCollision())
        return;

    if(isMove)
    {
        switch (dir)
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
    }

}


void Tank::moveForJudge()
{
    if(isMove==true)
    {
        switch(dir)
        {
        case UP:
            pos.setY(pos.y() + step);
            break;
        case DOWN:
            pos.setY(pos.y() - step);
            break;
        case LEFT:
            pos.setX(pos.x() + step);
            break;
        case RIGHT:
            pos.setX(pos.x() - step);
            break;
        }
        calSphere();
    }
}


void Tank::startMove()
{
    isMove = true;
}


void Tank::stopMove()
{
    isMove = false;
}


void Tank::fire()
{
    if(isDisappear() == true)
            return;

    if(isFire)
    {
        Missile* fire_missile = new Missile(*this);
        missilesOfTank.append(fire_missile);
    }
}


bool Tank::getIsFire()const
{
    return isFire;
}


void Tank::startFire()
{
    isFire = true;
}


void Tank::stopFire()
{
    isFire = false;
}


bool Tank::isToCollision()
{
    Tank judgeTank = *this;
    judgeTank.moveForJudge();


    QPoint nowPos = judgeTank.getPos();


    if(nowPos.x() < 0
            ||nowPos.x() > MAPWIDTH
            ||nowPos.y() < 0
            ||nowPos.y() > MAPHEIGHT)
        //碰撞地图边界
        return true;

    if(info.map->getCell(nowPos.x() / CELLWIDTH, nowPos.y() / CELLHEIGHT)->is_penetration_of_tank() == false)
       //碰撞到坦克无法穿越的地形
        return true;
    else
        return false;

    //玩家碰撞到敌方坦克

    //敌方坦克碰撞到玩家

    //敌方坦克碰撞到敌方坦克

}


void Tank::beAttacked(int attack)
{
    life -= attack;

    if(life <= 0)
    {
        setDisappear(true);
        life = 0;
    }

}
