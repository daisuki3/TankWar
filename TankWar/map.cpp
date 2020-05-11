#include "map.h"

Map::Map()
{
    for(int i=0;i<ROW;i++)
       for(int j=0;j<COL;j++)
           cells[i][j]=new Cell(i,j);
}

Map::~Map()
{
    for(int i=0;i<ROW;i++)
        for(int j=0;j<COL;j++)
        {
            if(cells[i][j] != NULL)
            {
                delete cells[i][j];
                cells[i][j] = NULL;
            }
        }
}

void Map::display(QPainter &paint)
{
    paint.setBrush(Qt::black);
    paint.setPen(Qt::black);
    paint.drawRect(0,0,MAPWIDTH,MAPHEIGHT);

    //paint.drawImage(QRect(0,0,WIDTH,HEIGHT),QImage(":/images/background.bmp"));

    for(int i=0;i<ROW;i++)
        for(int j=0;j<COL;j++)
            if(cells[i][j] != NULL)
                cells[i][j]->display(paint);
}

Cell* Map::getCell(int x, int y)const
{
    return cells[x][y];
}
