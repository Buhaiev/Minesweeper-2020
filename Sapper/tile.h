#ifndef TILE_H
#define TILE_H
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QPushButton>
#include "rightclickbutton.h"

class tile{
private:
int x;
int y;
int status; //0-closed 1-open 2-marked
QImage img;
rightClickButton* screenTile;
int contents;     //0 means empty; 1-8- amount of bombs around; 9-bomb
QVector<QPair<int, int>> closedNeighbors;
QVector<QPair<int, int>> markedNeighbors;
public:
void setEmpty();
void setNum();
rightClickButton* getButton();
void setButton(rightClickButton* but);
int getX();
void setX(int x);
int getY();
void setY(int y);
int getContent();
void setContent(int cont);
int getStatus();
void setStatus(int status);
void updateNeighbors(QVector<QPair<int, int>>, QVector<QPair<int, int>>);
void addClosedNeighbor(QPair<int, int>);
void addMarkedNeighbor(QPair<int, int>);
QVector<QPair<int, int>>  getClosedNeighbors();
QVector<QPair<int, int>>  getMarkedNeighbors();
tile();
tile(int x, int y);
~tile();
private slots:
    //void tileLeftClicked();
    //void tileRightClicked();
signals:
    //void mouseLeftClicked(tile* currTile);
    //void mouseRightClicked(tile* currTile);
//tile operator =(tile const &otherTile);
};

#endif // TILE_H
