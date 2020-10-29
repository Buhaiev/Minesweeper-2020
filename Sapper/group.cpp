#include "group.h"
//A group of tiles with a known amount of mines in them
group::group()
{

}

group::group(QVector<QPair<int, int>>vec, int mines)
{
    this->tiles=vec;
    this->mineNumber=mines;
}

void group::setTiles(QVector<QPair<int, int>>vec){
    this->tiles=vec;
}

void group::setMines(int mines){
    this->mineNumber=mines;
}

QVector<QPair<int, int>> group::getTiles(){
    return this->tiles;
}

int group::getMines(){
    return this->mineNumber;
}
