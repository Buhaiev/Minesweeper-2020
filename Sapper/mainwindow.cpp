#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>

const int cap=10;  //amount of tiles in a row or column
const int maxMines=15; //amount of mines on the field
const QImage empty(":/new/prefix1/img/closed_tile.xcf");
int tilesOpened=0;
int tilesChecked=0;
int mineCounter;
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
    ui->setupUi(this);
    QObject::connect(ui->newGameButton, SIGNAL(clicked()), this, SLOT(newGame()));
    for(int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){
            rightClickButton* myButton= new rightClickButton(this);
            myButton->setGeometry(100+40*i, 100+40*j,40,40);
            myButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            myButton->setRow(i);
            myButton->setCol(j);
            qApp->setStyleSheet("rightClickButton {font-size:30px; background-color:yellow;}");
            ui->gridLayout->addWidget(myButton,100+40*i, 100+40*j,40,40);
            tile* myTile=new tile(100+40*i, 100+40*j);
            tiles[i][j]= *myTile;
            tiles[i][j].setX(100+40*i);
            tiles[i][j].setY(100+40*j);
            tiles[i][j].setButton(myButton);
            connect(tiles[i][j].getButton(), SIGNAL(tileLeftClicked(int, int)), this, SLOT(onTileLeftClicked(int, int)));
            connect(tiles[i][j].getButton(), SIGNAL(tileRightClicked(int, int)), this, SLOT(onTileRightClicked(int, int)));
        }
    }
    newGame();
    for(int i=0; i<10; i++){
        newGame();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGame(){
    tilesOpened=0;
    tilesChecked=0;

    for(int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){

            tiles[i][j].getButton()->setText("");
            tiles[i][j].getButton()->setStyleSheet("background-color:yellow");
            tiles[i][j].setStatus(0);
            tiles[i][j].setContent(0);
        }
    }
    mineCounter=maxMines;
    ui->minesLeft->setText(QString::number(mineCounter));
    //placing bombs
    //qsrand(0);

    //srand(time(nullptr));

    for(int i=0; i<maxMines; i++){
        int a =rand()%10;
        int b =rand()%10;
        if(tiles[a][b].getContent()!=9){
            tiles[a][b].setContent(9);
        }else{
            i--;
        }
        tiles[a][b].getButton()->update();
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
               tiles[i][j].getButton()->update();
           }
       }
   }
}

void MainWindow:: onTileLeftClicked(int row, int col){
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
        auto reply=QMessageBox::question(this, "BOMB", "You lose. Try again?"+QString::number(row)+" "+QString::number(col));
        if(reply==QMessageBox::Yes){
            newGame();
        }else{
            close();
        }

    }else{
        currTile->getButton()->setStyleSheet("background-color:blue");
        currTile->getButton()->setText(QString::number(currTile->getContent()));
        currTile->getButton()->update();
    }

    bool isOver=true;
    for(int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){

            if(tiles[i][j].getStatus()==0){
                isOver=false;
            }
        }
    }
    if(isOver){
        QMessageBox::information(this, "You win!", "You have found all the bombs!");
    }
    updateAllNeigbors();
}

void MainWindow:: onTileRightClicked(int row, int col){
    tile* currTile=&tiles[row][col];
    if(currTile->getStatus()==0){
        ui->minesLeft->setText(QString::number(--mineCounter));
        tilesChecked++;
        currTile->setStatus(2);
        currTile->getButton()->setStyleSheet("background-color:red");
        currTile->getButton()->update();
    }else if(currTile->getStatus()==2){
        ui->minesLeft->setText(QString::number(++mineCounter));
        tilesChecked--;
        currTile->setStatus(0);
        currTile->getButton()->setStyleSheet("background-color:yellow");
    }else if(currTile->getStatus()==1){
        QString log="";
        for (int i=0; i<currTile->getClosedNeighbors().size(); i++){
            log+=QString::number(currTile->getClosedNeighbors()[i].first)+" "+QString::number(currTile->getClosedNeighbors()[i].second)+"\n";
        }
        log+="\n\n\n";
        for (int i=0; i<currTile->getMarkedNeighbors().size(); i++){
            log+=QString::number(currTile->getMarkedNeighbors()[i].first)+" "+QString::number(currTile->getMarkedNeighbors()[i].second)+"\n";
        }
        QMessageBox::information(this, " ", log);
    }

    bool isOver=true;
    for(int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){

            if(tiles[i][j].getStatus()==0){
                isOver=false;
            }
        }
    }
    if(isOver){
        QMessageBox::information(this, "You win!", "You have found all the bombs!");
    }
    updateAllNeigbors();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString log=QString::number(tilesOpened)+" "+QString::number(tilesChecked);
    QMessageBox::information(this, "numbers", log);
}

void MainWindow::on_solveButton_clicked()
{
    updateAllNeigbors();
    placeObvious();
    updateAllNeigbors();
    openSafeTiles();
    updateAllNeigbors();
    advancedChecking();
}

void MainWindow::openSafeTiles(){
    for (int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){
            if(tiles[i][j].getStatus()==1){
                if(tiles[i][j].getMarkedNeighbors().size()==tiles[i][j].getContent()){
                    for(int l=0; l<tiles[i][j].getClosedNeighbors().size(); l++){
                        onTileLeftClicked(tiles[i][j].getClosedNeighbors()[l].first, tiles[i][j].getClosedNeighbors()[l].second);
                    }
                }
            }
        }
    }
}

void MainWindow::placeObvious(){
    for (int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){
            if(tiles[i][j].getStatus()==1){
                if(tiles[i][j].getClosedNeighbors().size()+tiles[i][j].getMarkedNeighbors().size()==tiles[i][j].getContent()){
                    for(int l=0; l<tiles[i][j].getClosedNeighbors().size(); l++){
                        onTileRightClicked(tiles[i][j].getClosedNeighbors()[l].first, tiles[i][j].getClosedNeighbors()[l].second);
                    }
                }
            }
        }
    }
}

bool contains(QVector<QPair<int, int>> main, QVector<QPair<int, int>> add){
    for (int i=0; i<add.size(); i++){
        bool isHere=false;
        for (int j=0; j<main.size(); j++){
            if(main[j]==add[i]){
                isHere=true;
            }
        }
        if(!isHere){
            return false;
        }
    }
    return true;
}

void MainWindow::advancedChecking(){
    for (int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){
            qDebug()<<"     "<<i<<" "<<j;
            QVector<tile*> nearbyTiles;
            if((tiles[i][j].getStatus()==1)&&(tiles[i][j].getContent()>0)){
                if(i>0){
                    if((tiles[i-1][j].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i-1][j].getClosedNeighbors())))  nearbyTiles.append(&tiles[i-1][j]);
                    if(j>0){
                        if((tiles[i][j-1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i][j-1].getClosedNeighbors()))) nearbyTiles.append(&tiles[i][j-1]);
                        if((tiles[i-1][j-1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i-1][j-1].getClosedNeighbors()))) nearbyTiles.append(&tiles[i-1][j-1]);
                    }
                    if(j<9){
                        if((tiles[i][j+1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i][j+1].getClosedNeighbors()))) nearbyTiles.append(&tiles[i][j+1]);
                        if((tiles[i-1][j+1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i-1][j+1].getClosedNeighbors()))) nearbyTiles.append(&tiles[i-1][j+1]);
                    }
                }
                if(i<9){
                    if((tiles[i+1][j].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i+1][j].getClosedNeighbors()))) nearbyTiles.append(&tiles[i+1][j]);
                    if(j>0){
                        if(i==0){
                            if((tiles[i][j-1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i][j-1].getClosedNeighbors()))) nearbyTiles.append(&tiles[i][j-1]);
                        }
                        if((tiles[i+1][j-1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i+1][j-1].getClosedNeighbors()))) nearbyTiles.append(&tiles[i+1][j-1]);
                    }
                    if(j<9){
                        if(i==0){
                            if((tiles[i][j+1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i][j+1].getClosedNeighbors()))) nearbyTiles.append(&tiles[i][j+1]);
                        }
                        if((tiles[i+1][j+1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i+1][j+1].getClosedNeighbors()))) nearbyTiles.append(&tiles[i+1][j+1]);
                    }
                }
            }
            for (int l=0;l<nearbyTiles.size(); l++){
                qDebug()<<(nearbyTiles[l]->getX()-100)/40<<" "<<(nearbyTiles[l]->getY()-100)/40;
            }
            /*if(nearbyTiles.size()>0){
                QString log;
                log+=QString::number(i)+" "+QString::number(j)+"\n\n";
                for (int l=0; l<nearbyTiles.size(); l++){
                    log+=QString::number(nearbyTiles[l].first)+" "+QString::number(nearbyTiles[l].second)+"\n";
                }
                QMessageBox::information(this, "Neighbors", log);
            }*/

            for(int l=0; l<nearbyTiles.size(); l++){
                if(contains(tiles[i][j].getClosedNeighbors(),nearbyTiles[l]->getClosedNeighbors())){
                    QVector<QPair<int, int>> remainingGroup=tiles[i][j].getClosedNeighbors();
                    for(int a=0; a<nearbyTiles[l]->getClosedNeighbors().size(); a++){
                        for(int b=0; b<remainingGroup.size(); b++){
                            if(nearbyTiles[l]->getClosedNeighbors()[a]==remainingGroup[b]){
                                remainingGroup.erase(remainingGroup.begin()+b);
                                break;
                            }

                        }
                    }

                    qDebug()<<l<<remainingGroup.size();
                    /*QString log;
                    log+=QString::number(i)+" "+QString::number(j)+"    "+QString::number((nearbyTiles[l]->getX()-100)/40)+" "+QString::number((nearbyTiles[l]->getY()-100)/40)+"\n\n";
                    for (int k=0; k<remainingGroup.size(); k++){
                        log+=QString::number(remainingGroup[k].first)+" "+QString::number(remainingGroup[k].second)+"\n";
                    }
                    log+=QString::number(tiles[i][j].getContent())+" "+QString::number(tiles[i][j].getMarkedNeighbors().size())+"  "+QString::number(nearbyTiles[l]->getContent())+" "+QString::number(nearbyTiles[l]->getMarkedNeighbors().size());
                    QMessageBox::information(this, "Neighbors", log);*/

                    if((tiles[i][j].getContent()-tiles[i][j].getMarkedNeighbors().size())-(nearbyTiles[l]->getContent()-nearbyTiles[l]->getMarkedNeighbors().size())==0){
                        for (int k=0; k<remainingGroup.size(); k++){
                            onTileLeftClicked(remainingGroup[k].first,remainingGroup[k].second);
                        }
                    }else if((tiles[i][j].getContent()-tiles[i][j].getMarkedNeighbors().size())-(nearbyTiles[l]->getContent()-nearbyTiles[l]->getMarkedNeighbors().size())==remainingGroup.size()){
                        for (int k=0; k<remainingGroup.size(); k++){
                            onTileRightClicked(remainingGroup[k].first,remainingGroup[k].second);
                        }
                    }
                }
            }
            updateAllNeigbors();
        }
    }
}

void MainWindow::updateAllNeigbors(){
    for (int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){
            QVector<QPair<int, int>> vec1;
            tiles[i][j].updateNeighbors(vec1, vec1);
        }
    }
    for (int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){
            //QVector<QPair<int, int>> vec1;
            //tiles[i][j].updateNeighbors(vec1, vec1);
            if(tiles[i][j].getStatus()==0){
                if(i>0){
                    tiles[i-1][j].addClosedNeighbor(QPair<int, int>(i,j));
                    if(j>0){
                        tiles[i][j-1].addClosedNeighbor(QPair<int, int>(i,j));
                        tiles[i-1][j-1].addClosedNeighbor(QPair<int, int>(i,j));
                    }
                    if(j<9){
                        tiles[i][j+1].addClosedNeighbor(QPair<int, int>(i,j));
                        tiles[i-1][j+1].addClosedNeighbor(QPair<int, int>(i,j));
                    }
                }
                if(i<9){
                    tiles[i+1][j].addClosedNeighbor(QPair<int, int>(i,j));
                    if(j>0){
                        if(i==0){
                            tiles[i][j-1].addClosedNeighbor(QPair<int, int>(i,j));
                        }
                        tiles[i+1][j-1].addClosedNeighbor(QPair<int, int>(i,j));
                    }
                    if(j<9){
                        if(i==0){
                            tiles[i][j+1].addClosedNeighbor(QPair<int, int>(i,j));
                        }
                        tiles[i+1][j+1].addClosedNeighbor(QPair<int, int>(i,j));
                    }
                }
            }
            if(tiles[i][j].getStatus()==2){
                if(i>0){
                    tiles[i-1][j].addMarkedNeighbor(QPair<int, int>(i,j));
                    if(j>0){
                        tiles[i][j-1].addMarkedNeighbor(QPair<int, int>(i,j));
                        tiles[i-1][j-1].addMarkedNeighbor(QPair<int, int>(i,j));
                    }
                    if(j<9){
                        tiles[i][j+1].addMarkedNeighbor(QPair<int, int>(i,j));
                        tiles[i-1][j+1].addMarkedNeighbor(QPair<int, int>(i,j));
                    }
                }
                if(i<9){
                    tiles[i+1][j].addMarkedNeighbor(QPair<int, int>(i,j));
                    if(j>0){
                        if(i==0){
                            tiles[i][j-1].addMarkedNeighbor(QPair<int, int>(i,j));
                        }
                        tiles[i+1][j-1].addMarkedNeighbor(QPair<int, int>(i,j));
                    }
                    if(j<9){
                        if(i==0){
                            tiles[i][j+1].addMarkedNeighbor(QPair<int, int>(i,j));
                        }
                        tiles[i+1][j+1].addMarkedNeighbor(QPair<int, int>(i,j));
                    }
                }
            }
        }
    }
}
