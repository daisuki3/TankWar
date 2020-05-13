#ifndef BASE_H
#define BASE_H

#include <QPoint>
#include <QRect>
#include <QPainter>

enum Dir{UP, DOWN, LEFT, RIGHT};

class Base
{
private:
    QPoint pos;//左上角的点
    QRect rectSphere;//长方形（左上角坐标，长，宽）

    Dir dir;//方向

    bool disappear;//判断是否消失

    int life;//生命值
    int step;//移动
    int attack;//伤害

public:

    Base();

    friend class Boss;
    friend class Cell;

    friend class Missile;
    friend class Tank;

    virtual void display(QPainter &paint) = 0;

    virtual void move() = 0;

    virtual void beAttacked(int attack) = 0;

    virtual void calSphere() = 0;

    bool isDisappear();

    bool isBoom(const Base *base)const;//判断相撞

    void setDir(Dir dir);
    void setDisappear(bool dis);

    QPoint getPos() const;

};

#endif // BASE_H
