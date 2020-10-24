#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

const int cap=10;  //amount of tiles in a row or column
const QImage empty(":/new/prefix1/img/closed_tile.xcf");
int tilesOpened=0;
int tilesChecked=0;
tile** tiles;
QPainter painter;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    tiles=new tile* [cap];
    for(int i=0; i<cap; i++){
        tiles[i]=new tile[cap];
    }

    /*for(int i=0; i<cap; i++){
        tiles[i]=new tile[cap];
        for(int j=0; j<cap; j++){
            tile* myTile=new tile(100+40*i, 100+40*j);
            //tile* myTile=new tile();
            //QMessageBox::information(this, "Alert",QString::number(myTile->getX()));
            QPushButton* butt=myTile->getButton();
            if(butt==nullptr){
                QMessageBox::critical(this, "Alert","nullptr!");
            }
            tiles[i][j]= *myTile;
            ui->gridLayout->addWidget(butt,100+40*i, 100+40*j,40,40);
        }
    }*/
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    tilesOpened=0;
    tilesChecked=0;
    /*tile newTile(100,100);
    for(int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){
            QPushButton* myButton= new QPushButton(this);
            myButton->setGeometry(100+40*i, 100+40*j,40,40);
            myButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            ui->gridLayout->addWidget(myButton,100+40*i, 100+40*j,40,40);
        }
    }*/
    for(int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){
            rightClickButton* myButton= new rightClickButton(this);
            myButton->setGeometry(100+40*i, 100+40*j,40,40);
            myButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            myButton->setRow(i);
            myButton->setCol(j);
            //myButton->setStyleSheet("rightClickButton {font-size:200%}");
            //qApp->setStyleSheet("rightClickButton {background-color:yellow}");
            qApp->setStyleSheet("rightClickButton {font-size:30px; background-color:yellow}");
            //ui->gridLayout->addWidget(myButton,100+40*i, 100+40*j,40,40);
            tile* myTile=new tile(100+40*i, 100+40*j);
            tiles[i][j]= *myTile;
            tiles[i][j].setX(100+40*i);
            tiles[i][j].setY(100+40*j);
            tiles[i][j].setButton(myButton);
            connect(tiles[i][j].getButton(), SIGNAL(tileLeftClicked(int, int)), this, SLOT(onTileLeftClicked(int, int)));
            connect(tiles[i][j].getButton(), SIGNAL(tileRightClicked(int, int)), this, SLOT(onTileRightClicked(int, int)));
            //qDebug()<<connect(tiles[i][j].getButton(), SIGNAL(tileLeftClicked(int row, int col)), this, SLOT(onTileLeftClicked(int row, int col)));
            //tiles[i][j].getButton()->dumpObjectInfo();
            //connect(tiles[i][j].getButton(), SIGNAL(clicked()), this, SLOT(tiles[i][j].tileRightClicked()));
            //connect(tiles[i][j], SIGNAL(tileLeftClicked()), this, SLOT(mouseLeftClicked()));
            //connect(tiles[i][j].getButton(), SIGNAL(clicked()), this, SLOT(onTileLeftClicked(int row, int col)));
        }
    }
    fillBoard();
    /*QPushButton* myButton= new QPushButton("new button", this);
    myButton->setGeometry(100, 100,40,40);
    ui->gridLayout->addWidget(myButton, 100, 100, 40, 40);
    myButton->setGeometry(100, 100,40,40);*/
}

void MainWindow::fillBoard(){
    //placing bombs
    //qsrand(0);
    qsrand(time(nullptr));
    for(int i=0; i<cap; i++){
        int a =rand()%10;
        int b =rand()%10;
        //QMessageBox::information(this, "num", QString::number(a));
        //tile* currTile= &tiles[a][b];
        if(tiles[a][b].getContent()!=9){
            tiles[a][b].setContent(9);
        }else{
            i--;
        }
        //tiles[a][b].getButton()->setText("9");
        tiles[a][b].getButton()->update();
        //ui->gridLayout->update();
    }

    //setting numbers
    for(int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){
            if(tiles[i][j].getContent()==9){
                if(i>0){
                    if(tiles[i-1][j].getContent()!=9){
                        tiles[i-1][j].setContent(tiles[i-1][j].getContent()+1);
                    }
                    if(j>0){
                        if(tiles[i-1][j-1].getContent()!=9){
                            tiles[i-1][j-1].setContent(tiles[i-1][j-1].getContent()+1);
                        }
                        if(tiles[i][j-1].getContent()!=9){
                            if(i==9){
                                tiles[i][j-1].setContent(tiles[i][j-1].getContent()+1);
                            }
                        }
                    }
                    if(j<9){
                        if(tiles[i-1][j+1].getContent()!=9){
                            tiles[i-1][j+1].setContent(tiles[i-1][j+1].getContent()+1);
                        }
                        if(tiles[i][j+1].getContent()!=9){
                            if(i==9){
                                tiles[i][j+1].setContent(tiles[i][j+1].getContent()+1);
                            }
                        }
                    }
                }
                if(i<9){
                    if(tiles[i+1][j].getContent()!=9){
                        tiles[i+1][j].setContent(tiles[i+1][j].getContent()+1);
                    }
                    if(j>0){
                        if(tiles[i+1][j-1].getContent()!=9){
                            tiles[i+1][j-1].setContent(tiles[i+1][j-1].getContent()+1);
                        }
                        if(tiles[i][j-1].getContent()!=9){
                            tiles[i][j-1].setContent(tiles[i][j-1].getContent()+1);
                        }
                    }
                    if(j<9){
                        if(tiles[i+1][j+1].getContent()!=9){
                            tiles[i+1][j+1].setContent(tiles[i+1][j+1].getContent()+1);
                        }
                        if(tiles[i][j+1].getContent()!=9){
                            tiles[i][j+1].setContent(tiles[i][j+1].getContent()+1);
                        }
                    }
                }
            }
        }
    }
   for(int i=0; i<cap; i++){
       for(int j=0; j<cap; j++){
           if(tiles[i][j].getContent()!=0){
               //tiles[i][j].getButton()->setText(QString::number(tiles[i][j].getContent()));
               tiles[i][j].getButton()->update();
           }
       }
   }
}

void MainWindow:: onTileLeftClicked(int row, int col){
    //QString log= QString::number(row)+" "+QString::number(col);
    //QMessageBox::information(this, "this", log);
    tile* currTile=&tiles[row][col];
    tilesOpened++;
    currTile->setStatus(1);
    if(currTile->getContent()==0){
        currTile->getButton()->setStyleSheet("background-color:white");
        if(row>0){
            if(tiles[row-1][col].getStatus()==0){
                onTileLeftClicked(row-1, col);
            }
            if(col>0){
                if(tiles[row-1][col-1].getStatus()==0){
                    onTileLeftClicked(row-1, col-1);
                }
                if(tiles[row][col-1].getStatus()==0){
                    onTileLeftClicked(row, col-1);
                }
            }
            if(col<9){
                if(tiles[row-1][col+1].getStatus()==0){
                    onTileLeftClicked(row-1, col+1);
                }
                if(tiles[row][col+1].getStatus()==0){
                    onTileLeftClicked(row, col+1);
                }
            }
        }
        if(row<9){
            if(tiles[row+1][col].getStatus()==0){
                onTileLeftClicked(row+1, col);
            }
            if(col>0){
                if(tiles[row+1][col].getStatus()==0){
                    onTileLeftClicked(row+1, col-1);
                }
                if(tiles[row][col-1].getStatus()==0){
                    onTileLeftClicked(row, col-1);
                }
            }
            if(col<9){
                if(tiles[row+1][col+1].getStatus()==0){
                    onTileLeftClicked(row+1, col+1);
                }
                if(tiles[row][col+1].getStatus()==0){
                    onTileLeftClicked(row, col+1);
                }
            }
        }
        currTile->getButton()->update();
    }
    else if(currTile->getContent()==9){
        QMessageBox::critical(this, "BOMB", "You lose");
        on_pushButton_clicked();
    }else{
        currTile->getButton()->setText(QString::number(currTile->getContent()));
        currTile->getButton()->update();
    }
    if((tilesChecked==10)&&(tilesOpened==90)){
        QMessageBox::information(this, "You win!", "You have found all the bombs!");
    }
}

void MainWindow:: onTileRightClicked(int row, int col){
    tile* currTile=&tiles[row][col];
    //tiles[currTile->getX()][currTile->getY()].getButton()->setText(QString::number(tiles[currTile->getX()][currTile->getY()].getContent()));
    if(currTile->getStatus()!=2){
        tilesChecked++;
        currTile->setStatus(2);
        currTile->getButton()->setStyleSheet("background-color:red");
        currTile->getButton()->update();
    }else{
        tilesChecked--;
        currTile->setStatus(0);
        currTile->getButton()->setStyleSheet("background-color:yellow");
    }
    if((tilesChecked==10)&&(tilesOpened==90)){
        QMessageBox::information(this, "You win!", "You have found all the bombs!");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString log=QString::number(tilesOpened)+" "+QString::number(tilesChecked);
    QMessageBox::information(this, "numbers", log);
}
