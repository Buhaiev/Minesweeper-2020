#ifndef RIGHTCLICKBUTTON_H
#define RIGHTCLICKBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QMessageBox>

class rightClickButton: public QPushButton
{
    Q_OBJECT
public:
    explicit rightClickButton(QWidget* parent=0);
    void setRow(int row);
    int getRow();
    void setCol(int col);
    int getCol();
private:
    int row=0;    //i
    int col=0;    //j
private slots:
    void mousePressEvent(QMouseEvent *event);
signals:
    void tileLeftClicked(int row, int col);
    void tileRightClicked(int row, int col);
};

#endif // RIGHTCLICKBUTTON_H
