#include "rightclickbutton.h"

rightClickButton::rightClickButton(QWidget* parent): QPushButton(parent)
{

}

void rightClickButton::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::RightButton){
        emit tileRightClicked(this->row, this->col);
    }
    if(event->button()==Qt::LeftButton){
        //QMessageBox::information(this, "clicked", "leftClick");
        emit tileLeftClicked(this->row, this->col);
    }
}

void  rightClickButton::setRow(int row){
    this->row=row;
}
int  rightClickButton::getRow(){
    return this->row;
}
void  rightClickButton::setCol(int col){
    this->col=col;
}
int  rightClickButton::getCol(){
    return this->col;
}
