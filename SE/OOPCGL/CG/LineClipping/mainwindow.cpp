#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
using namespace std;

#include<QPainter>
#include<QTextEdit>
#include<QImage>
#include<QPixmap>
#include<QLine>
#include<QLabel>

QImage img(300, 300, QImage::Format_RGB888);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter qp(this);
    myfunction(&qp);
}


void MainWindow::myfunction(QPainter *qp) {
    QPen pen(Qt::blue, 2, Qt::SolidLine);
    qp->setPen(pen);
    qp->drawLine(200, 200, 400, 200);
    qp->drawLine(400, 200, 400, 400);
    qp->drawLine(400, 400, 200, 400);
    qp->drawLine(200, 400, 200, 200);

    float x1, y1, x2, y2;
    char c[4], d[4];

    x1=250;
    y1=300;
    x2=450;
    y2=450;

    float m = float((y2-y1)/(x2-x1));
    code(c, x1, y1);
    code(d, x2, y2);
    clipping(c, d, x1, y1, m);
    clipping(d, c, x2, y2, m);

    qp->setPen(QPen(Qt::red));
    qp->drawLine(x1, y1, x2, y2);
}


void MainWindow::code(char c[4], float x, float y) {
    c[0] = (y<200)?'1':'0';  //top - msb
    c[1] = (y>400)?'1':'0';  //bottom
    c[2] = (x>400)?'1':'0';  //right
    c[3] = (x<200)?'1':'0';  //left - lsb
}


void MainWindow::clipping(char c[], char d[], float &x, float &y, float m) {
    int flag=0;
    int i;

    for (i=0; i<4; i++) {
        if (c[i]!='0' && d[i]!='0') {  //completely inside
            flag = 1;
            break;
        }

        if (flag==0) {
            if (c[0]!='0') {  //top
                x = ((200-y)/m)+x;
                y=200;
            }
            else if (c[1]!='0') {  //bottom
                x=((400-y)/m)+x;
                y=400;
            }
            else if (c[2]!='0') {  //right
                y=m*(400-x)+y;
                x=400;
            }
            else if (c[3]!='0') {  //left
                y=m*(200-x)+y;
                x=200;
            }
        }
    }
}
