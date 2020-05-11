#ifndef BASE_H
#define BASE_H

#include <QPoint>
#include <QRect>
#include <QPainter>

enum Dir{UP, DOWN, LEFT, RIGHT};

class Base
{
private:
    QPoint pos;
    QRect rectSphere;

    Dir dir;

    bool disappear;

    int life;
    int step;
    int attack;

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

    bool isBoom(const Base *base)const;

    void setDisappear(bool dis);

    QPoint getPos() const;

};

#endif // BASE_H
