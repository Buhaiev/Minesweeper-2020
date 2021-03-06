#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>

const int cap=10;  //amount of tiles in a row or column
const int maxMines=40; //amount of mines on the field
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
    QObject::connect(ui->checkButton, SIGNAL(clicked()), this, SLOT(checkAll()));
    //checkButton.show();
    for(int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){
            rightClickButton* myButton= new rightClickButton(this);
            myButton->setGeometry(100+(400/cap)*i, 100+(400/cap)*j,400/cap,400/cap);
            myButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            myButton->setRow(i);
            myButton->setCol(j);
            qApp->setStyleSheet("rightClickButton {font-size:30px; background-color:yellow;}");
            ui->gridLayout->addWidget(myButton,100+(400/cap)*i, 100+(400/cap)*j,(400/cap),(400/cap));
            tile* myTile=new tile(100+(400/cap)*i, 100+(400/cap)*j);
            tiles[i][j]= *myTile;
            tiles[i][j].setX(100+(400/cap)*i);
            tiles[i][j].setY(100+(400/cap)*j);
            tiles[i][j].setButton(myButton);
            connect(tiles[i][j].getButton(), SIGNAL(tileLeftClicked(int, int)), this, SLOT(onTileLeftClicked(int, int)));
            connect(tiles[i][j].getButton(), SIGNAL(tileRightClicked(int, int)), this, SLOT(onTileRightClicked(int, int)));
        }
    }
    newGame();
    /*for(int i=0; i<10; i++){
        newGame();
    }*/
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
        int a =rand()%cap;
        int b =rand()%cap;
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
                            if(i==cap-1){
                                tiles[i][j-1].setContent(tiles[i][j-1].getContent()+1);
                            }
                        }
                    }
                    if(j<cap-1){
                        if(tiles[i-1][j+1].getContent()!=9){
                            tiles[i-1][j+1].setContent(tiles[i-1][j+1].getContent()+1);
                        }
                        if(tiles[i][j+1].getContent()!=9){
                            if(i==cap-1){
                                tiles[i][j+1].setContent(tiles[i][j+1].getContent()+1);
                            }
                        }
                    }
                }
                if(i<cap-1){
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
                    if(j<cap-1){
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
   updateAllNeigbors();
   checkNearbyGroups();
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
            if(col<cap-1){
                if(tiles[row-1][col+1].getStatus()==0){
                    onTileLeftClicked(row-1, col+1);
                }
                if(tiles[row][col+1].getStatus()==0){
                    onTileLeftClicked(row, col+1);
                }
            }
        }
        if(row<cap-1){
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
            if(col<cap-1){
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
        currTile->getButton()->setStyleSheet("background-color:red; border-radius: 5px");
        auto reply=QMessageBox::question(this, "BOMB", "You lose. Try again?");
        if(reply==QMessageBox::Yes){
            newGame();
        }else{
            //close();
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
    checkNearbyGroups();
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
        log+="\n\n\n";
        for (int i=0; i<currTile->getNearbyGroups().size(); i++){
            for(int j=0; j<currTile->getNearbyGroups()[i].getTiles().size(); j++){
                log+=QString::number(currTile->getNearbyGroups()[i].getTiles()[j].first)+" "+QString::number(currTile->getNearbyGroups()[i].getTiles()[j].second)+"\n";
            }
            log+=QString::number(currTile->getNearbyGroups()[i].getMines())+'\n';
            log+='\n';
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
    checkNearbyGroups();
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
    checkNearbyGroups();
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

bool noCommon(group grp1, group  grp2){
    for(int i=0; i<grp1.getTiles().size();i++){
        for(int j=0; j<grp2.getTiles().size(); j++){
            if((grp1.getTiles()[i].first==grp2.getTiles()[j].first)and(grp1.getTiles()[i].second==grp2.getTiles()[j].second)){
                return false;
            }
        }
    }
    return true;
}
void MainWindow::advancedChecking(){
    for (int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){
            //qDebug()<<"     "<<i<<" "<<j;
            int temp1=0;
            while(temp1<tiles[i][j].getNearbyGroups().size()){
                int temp2=0;
                while(temp2<tiles[i][j].getNearbyGroups().size()){
                    //qDebug()<<temp1<<" "<<temp2;
                    if((tiles[i][j].getNearbyGroups()[temp1].getTiles().size()!=0)and(tiles[i][j].getNearbyGroups()[temp2].getTiles().size()!=0)){
                        if(noCommon(tiles[i][j].getNearbyGroups()[temp1], tiles[i][j].getNearbyGroups()[temp2])){
                            QVector<QPair<int, int>> newVector;
                            for(int a=0; a<tiles[i][j].getNearbyGroups()[temp1].getTiles().size(); a++){
                                newVector.append(tiles[i][j].getNearbyGroups()[temp1].getTiles()[a]);
                            }
                            for(int b=0; b<tiles[i][j].getNearbyGroups()[temp2].getTiles().size(); b++){
                                newVector.append(tiles[i][j].getNearbyGroups()[temp2].getTiles()[b]);
                            }
                            tiles[i][j].addNearbyGroup(group(newVector, tiles[i][j].getNearbyGroups()[temp1].getMines()+tiles[i][j].getNearbyGroups()[temp2].getMines()));
                        }
                        for(int a=0; a<tiles[i][j].getNearbyGroups().size(); a++){
                            for(int b=0; b<tiles[i][j].getNearbyGroups()[a].getTiles().size(); b++){
                                qDebug()<<tiles[i][j].getNearbyGroups()[a].getTiles()[b].first<<" "<<tiles[i][j].getNearbyGroups()[a].getTiles()[b].second;
                            }
                            qDebug()<<" ";
                        }
                    }
                    temp2++;
                }
                temp1++;
            }
            /*for(int temp1=0; temp1<tiles[i][j].getNearbyGroups().size(); temp1++){
                for(int temp2=0; temp2<tiles[i][j].getNearbyGroups().size(); temp2++){
                    bool temp=noCommon(tiles[i][j].getNearbyGroups()[temp1], tiles[i][j].getNearbyGroups()[temp2]);
                    if(temp){
                        for(int temp3=0; temp3<tiles[i][j].getNearbyGroups()[temp1].getTiles().size(); temp3++){
                            qDebug()<<tiles[i][j].getNearbyGroups()[temp1].getTiles()[temp3].first<<" "<<tiles[i][j].getNearbyGroups()[temp1].getTiles()[temp3].second;
                        }
                        for(int temp4=0; temp4<tiles[i][j].getNearbyGroups()[temp2].getTiles().size(); temp4++){
                            qDebug()<<tiles[i][j].getNearbyGroups()[temp2].getTiles()[temp4].first<<" "<<tiles[i][j].getNearbyGroups()[temp2].getTiles()[temp4].second;
                        }
                    }
                }
            }*/
            for(int l=0; l<tiles[i][j].getNearbyGroups().size(); l++){
                for(int k=0; k<tiles[i][j].getNearbyGroups().size(); k++){
                    if((k!=l)and(tiles[i][j].getNearbyGroups()[l].getTiles()!=tiles[i][j].getNearbyGroups()[k].getTiles())){
                        if(contains(tiles[i][j].getNearbyGroups()[l].getTiles(), tiles[i][j].getNearbyGroups()[k].getTiles())){
                            QVector<QPair<int, int>> leftTiles;
                            for(int t1=0; t1<tiles[i][j].getNearbyGroups()[l].getTiles().size(); t1++){
                                bool isPresent=false;
                                for(int t2=0; t2<tiles[i][j].getNearbyGroups()[k].getTiles().size(); t2++){

                                    //qDebug()<<tiles[i][j].getNearbyGroups()[l].getTiles().size()<<" "<<tiles[i][j].getNearbyGroups()[k].getTiles().size();
                                    /*if((i==1)&&(j==6)){
                                        qDebug()<<"     "<<tiles[i][j].getNearbyGroups()[l].getMines()<<" "<<tiles[i][j].getNearbyGroups()[k].getMines();
                                        qDebug()<<"             "<<l<<" "<<k<<" "<<t1<<" "<<t2;
                                        for(int iter=0; iter<tiles[i][j].getNearbyGroups().size(); iter++){
                                            for(int iter2=0; iter2<tiles[i][j].getNearbyGroups()[iter].getTiles().size(); iter2++){
                                                qDebug()<<tiles[i][j].getNearbyGroups()[iter].getTiles()[iter2].first<<" "<<tiles[i][j].getNearbyGroups()[iter].getTiles()[iter2].second;
                                            }
                                            qDebug()<<tiles[i][j].getNearbyGroups()[iter].getMines();
                                            qDebug()<<" ";
                                        }
                                    }*/

                                    if(tiles[i][j].getNearbyGroups()[l].getTiles()[t1]==tiles[i][j].getNearbyGroups()[k].getTiles()[t2]){
                                        isPresent=true;
                                        break;
                                    }
                                }
                                if(!isPresent){
                                    leftTiles.append(QPair<int, int>(tiles[i][j].getNearbyGroups()[l].getTiles()[t1]));
                                }

                            }
                            if(tiles[i][j].getNearbyGroups()[l].getMines()==tiles[i][j].getNearbyGroups()[k].getMines()){
                                for(int t=0; t<leftTiles.size(); t++){
                                    //qDebug()<<i<<" "<<j<<" "<<l<<" "<<k<<" "<<t;
                                    onTileLeftClicked(leftTiles[t].first,leftTiles[t].second);
                                }
                            }
                            else if(tiles[i][j].getNearbyGroups()[l].getMines()-tiles[i][j].getNearbyGroups()[k].getMines()==leftTiles.size()){
                                for(int t=0; t<leftTiles.size(); t++){
                                    //qDebug()<<i<<" "<<j<<" "<<l<<" "<<k<<" "<<t;
                                    onTileRightClicked(leftTiles[t].first,leftTiles[t].second);
                                }
                            }
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


void MainWindow::checkNearbyGroups(){
    for (int i=0; i<cap; i++){
        for(int j=0; j<cap; j++){
            //qDebug()<<"     "<<i<<" "<<j;
            QVector<group> nearbyGroups;
            nearbyGroups.append(group(tiles[i][j].getClosedNeighbors(), tiles[i][j].getContent()-tiles[i][j].getMarkedNeighbors().size()));
            if((i==1)&&(j==3)){
                //qDebug()<<"     "<<tiles[i][j].getContent()<<" "<<tiles[i][j].getMarkedNeighbors().size();
                //qDebug()<<"     "<<nearbyGroups[0].getMines();
            }
            if((tiles[i][j].getStatus()==1)&&(tiles[i][j].getContent()>0)){
                if(i>0){
                    if((tiles[i-1][j].getStatus()==1)and(tiles[i-1][j].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i-1][j].getClosedNeighbors())))  nearbyGroups.append(group(tiles[i-1][j].getClosedNeighbors(), tiles[i-1][j].getContent()-tiles[i-1][j].getMarkedNeighbors().size()));
                    if(j>0){
                        if((tiles[i][j-1].getStatus()==1)and(tiles[i][j-1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i][j-1].getClosedNeighbors()))) nearbyGroups.append(group(tiles[i][j-1].getClosedNeighbors(), tiles[i][j-1].getContent()-tiles[i][j-1].getMarkedNeighbors().size()));
                        if((tiles[i-1][j-1].getStatus()==1)and(tiles[i-1][j-1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i-1][j-1].getClosedNeighbors()))) nearbyGroups.append(group(tiles[i-1][j-1].getClosedNeighbors(), tiles[i-1][j-1].getContent()-tiles[i-1][j-1].getMarkedNeighbors().size()));
                    }
                    if(j<9){
                        if((tiles[i][j+1].getStatus()==1)and(tiles[i][j+1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i][j+1].getClosedNeighbors()))) nearbyGroups.append(group(tiles[i][j+1].getClosedNeighbors(), tiles[i][j+1].getContent()-tiles[i][j+1].getMarkedNeighbors().size()));
                        if((tiles[i-1][j+1].getStatus()==1)and(tiles[i-1][j+1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i-1][j+1].getClosedNeighbors()))) nearbyGroups.append(group(tiles[i-1][j+1].getClosedNeighbors(), tiles[i-1][j+1].getContent()-tiles[i-1][j+1].getMarkedNeighbors().size()));
                    }
                }
                if(i<9){
                    if((tiles[i+1][j].getStatus()==1)and(tiles[i+1][j].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i+1][j].getClosedNeighbors()))) nearbyGroups.append(group(tiles[i+1][j].getClosedNeighbors(), tiles[i+1][j].getContent()-tiles[i+1][j].getMarkedNeighbors().size()));
                    if(j>0){
                        if(i==0){
                            if((tiles[i][j-1].getStatus()==1)and(tiles[i][j-1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i][j-1].getClosedNeighbors()))) nearbyGroups.append(group(tiles[i][j-1].getClosedNeighbors(), tiles[i][j-1].getContent()-tiles[i][j-1].getMarkedNeighbors().size()));
                        }
                        if((tiles[i+1][j-1].getStatus()==1)and(tiles[i+1][j-1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i+1][j-1].getClosedNeighbors()))) nearbyGroups.append(group(tiles[i+1][j-1].getClosedNeighbors(), tiles[i+1][j-1].getContent()-tiles[i+1][j-1].getMarkedNeighbors().size()));
                    }
                    if(j<9){
                        if(i==0){
                            if((tiles[i][j+1].getStatus()==1)and(tiles[i][j+1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i][j+1].getClosedNeighbors()))) nearbyGroups.append(group(tiles[i][j+1].getClosedNeighbors(), tiles[i][j+1].getContent()-tiles[i][j+1].getMarkedNeighbors().size()));
                        }
                        if((tiles[i+1][j+1].getStatus()==1)and(tiles[i+1][j+1].getClosedNeighbors().size()!=0)and(contains(tiles[i][j].getClosedNeighbors(),tiles[i+1][j+1].getClosedNeighbors()))) nearbyGroups.append(group(tiles[i+1][j+1].getClosedNeighbors(), tiles[i+1][j+1].getContent()-tiles[i+1][j+1].getMarkedNeighbors().size()));
                    }
                }
            }
            tiles[i][j].updateNearbyGroups(nearbyGroups);

        }
    }
    /*for(int k=0; k<tiles[1][3].getNearbyGroups().size(); k++){
        for(int l=0; l<tiles[1][3].getNearbyGroups()[k].getTiles().size(); l++){
            qDebug()<<QString::number(tiles[1][3].getNearbyGroups()[k].getTiles()[l].first)+" "+QString::number(tiles[1][3].getNearbyGroups()[k].getTiles()[l].second);
        }
        qDebug()<<QString::number(tiles[1][3].getNearbyGroups()[k].getMines());
        qDebug()<<" ";
    }*/
}

void MainWindow::checkAll(){
    updateAllNeigbors();
    checkNearbyGroups();
}
