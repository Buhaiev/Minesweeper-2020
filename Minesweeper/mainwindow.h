#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <math.h>
#include <QMessageBox>
#include "tile.h"
#include "rightclickbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    //QPushButton* myButton;
private slots:
    void on_pushButton_clicked();
    void fillBoard();
    //void mouseRightClicked(tile* currTile);
    //void mouseLeftClicked(tile* currTile);
    void on_pushButton_2_clicked();

public slots:
    void onTileLeftClicked(int row, int col);
    void onTileRightClicked(int row, int col);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
