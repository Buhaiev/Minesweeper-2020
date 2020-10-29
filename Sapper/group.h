#ifndef GROUP_H
#define GROUP_H
#include <QVector>

class tile;

class group{
private:
   QVector<QPair<int, int>> tiles;
   int mineNumber;
public:
    group();
    group(QVector<QPair<int, int>>, int);
    void setTiles(QVector<QPair<int, int>>);
    void setMines(int);
    QVector<QPair<int, int>> getTiles();
    int getMines();
};

#endif // GROUP_H
