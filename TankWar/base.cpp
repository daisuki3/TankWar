#include "base.h"

Base::Base()
{

}

bool Base::isDisappear()
{
    return disappear;
}

bool Base::isBoom(const Base *base) const
{

    if(disappear == true
            ||base->disappear == true
            ||base->rectSphere.left() > rectSphere.right()
            ||base->rectSphere.right() < rectSphere.left()
            ||base->rectSphere.top() > rectSphere.bottom()
            ||base->rectSphere.bottom() < rectSphere.top()
            )
        return false;

    return true;
}

void Base::setDir(Dir dir)
{
    this->dir = dir;
}

void Base::setDisappear(bool dis)
{
    this->disappear = dis;
}

QPoint Base::getPos() const
{
    return pos;
}

