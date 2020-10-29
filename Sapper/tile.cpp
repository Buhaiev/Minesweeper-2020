#include <tile.h>
#include <QPainter>
#include <QMessageBox>

tile::tile(){
    this->x=100;
    this->y=100;
    img.load(":/new/prefix1/img/closed tile.xcf");
    QPainter painter;
    painter.drawImage(x,y,img);
    screenTile=new rightClickButton();
    screenTile->setGeometry(x, y,40,40);
    screenTile->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    contents=0;
    status=0;
}

tile::tile(int x, int y){
    this->x=x;
    this->y=y;
    screenTile=new rightClickButton();
    screenTile->setGeometry(x, y,40,40);
    screenTile->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    contents=0;
    status=0;
}

tile::~tile(){
    delete screenTile;
}

rightClickButton* tile::getButton(){
    return this->screenTile;
}

void tile::setButton(rightClickButton* but){
    this->screenTile=but;
}
int tile::getX(){
    return this->x;
}
void tile::setX(int x){
    this->x=x;
}
int tile::getY(){
    return this->y;
}
void tile::setY(int y){
    this->y=y;
}

int tile::getContent(){
    return contents;
}

void tile::setContent(int cont){
    this->contents=cont;
}

int tile::getStatus(){
    return status;
}

void tile::setStatus(int status){
    this->status=status;
}

void tile::updateNeighbors(QVector<QPair<int, int> > vec1, QVector<QPair<int, int> > vec2){
    this->closedNeighbors=vec1;
    this->markedNeighbors=vec2;
}

void tile::updateNearbyGroups(QVector<group> vec){
    this->nearbyGroups=vec;
}

QVector<QPair<int, int> >  tile::getClosedNeighbors(){
    return (this->closedNeighbors);
}

QVector<QPair<int, int> >  tile::getMarkedNeighbors(){
    return (this->markedNeighbors);
}

QVector<group >  tile::getNearbyGroups(){
    return (this->nearbyGroups);
}

void tile::addClosedNeighbor(QPair<int, int> pair){
    this->closedNeighbors.append(pair);
}

void tile::addMarkedNeighbor(QPair<int, int> pair){
    this->markedNeighbors.append(pair);
}

void tile::addNearbyGroup(group grp){
    this->nearbyGroups.append(grp);
}
