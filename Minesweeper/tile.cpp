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
    //img.load(":/new/prefix1/img/closed tile.xcf");
    this->x=x;
    this->y=y;
    //this->screenTile=new QPushButton();
    screenTile=new rightClickButton();
    screenTile->setGeometry(x, y,40,40);
    screenTile->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //screenTile->setGeometry(x, y, 40,40);
    contents=0;
    status=0;
}

tile::~tile(){

}

rightClickButton* tile::getButton(){
    //if(this->screenTile==nullptr)
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

/*void tile::tileLeftClicked(){
    emit mouseLeftClicked(this);
}

void tile::tileRightClicked(){
    emit mouseRightClicked(this);
}*/
//tile tile::operator =(tile const &otherTile){
    //this->
//}
