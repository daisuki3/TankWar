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

void Map::loadMap()
{             /*col代表x坐标
                row代表 y坐标
            const int BOSS = 0;
            const int WALL = 1;
            const int STEEL = 2;
            const int WATER = 3;
            const int GROUND = 4;

                */
    int map_1[COL][ROW]={
               //1,2,3,4,5,6,7,8,9,0,1,2,3
                {GROUND,GROUND,GROUND,GROUND,GROUND,GROUND,GROUND,GROUND,GROUND,GROUND,GROUND,GROUND,GROUND},
                {GROUND,WALL,GROUND,WALL,GROUND,GROUND,GROUND,GROUND,GROUND,WALL,GROUND,WALL,GROUND},
                {GROUND,WALL,GROUND,WALL,GROUND,STEEL,GROUND,STEEL,GROUND,WALL,GROUND,WALL,GROUND},
                {GROUND,WALL,GROUND,WALL,GROUND,STEEL,GROUND,STEEL,GROUND,WALL,GROUND,WALL,GROUND},
                {4,1,4,1,4,2,4,2,4,1,4,1,4},
                {4,4,4,4,4,4,4,4,4,4,4,4,4},
                {2,4,1,1,4,4,4,4,4,1,1,2,2},
                {4,4,4,4,4,1,1,1,4,4,4,2,0},
                {4,1,4,1,4,1,1,1,4,1,4,2,2},
                {4,1,4,1,4,1,4,1,4,1,4,1,4},
                {4,1,4,1,4,4,4,4,4,1,4,1,4},
                {4,1,4,1,4,1,1,WATER,4,1,4,1,4},
                {4,4,4,4,4,1,4,1,4,4,4,4,4},
            };



            for(int i=0;i<ROW;++i)
                for(int j=0;j<COL;++j)
                    cells[i][j]=new Cell(i,j,map_1[i][j]);


}

void Map::display(QPainter &paint)
{
    paint.setBrush(Qt::black);
    paint.setPen(Qt::black);
    paint.drawRect(0,0,MAPWIDTH,MAPHEIGHT);



    for(int i=0;i<ROW;i++)
        for(int j=0;j<COL;j++)
            if(cells[i][j] != NULL)
                cells[i][j]->display(paint);
}

Cell* Map::getCell(int x, int y)const
{
    return cells[x][y];
}
