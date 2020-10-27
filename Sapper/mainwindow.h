#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <math.h>
#include "tile.h"
#include "rightclickbutton.h"
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void newGame();
    void on_pushButton_2_clicked();

    void updateAllNeigbors();
    void placeObvious();
    void openSafeTiles();
    void advancedChecking();
    void on_solveButton_clicked();

public slots:
    void onTileLeftClicked(int row, int col);
    void onTileRightClicked(int row, int col);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
