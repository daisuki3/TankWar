#ifndef MAP_H
#define MAP_H

#include "cell.h"
#include "main.h"

#include <QRect>
#include <QPainter>


class Map
{

private:
    Cell* cells[ROW][COL];

public:
    Map();
    ~Map();

    Cell* getCell(int x, int y)const;

    void loadMap();

    void display(QPainter &paint);

};

#endif // MAP_H
