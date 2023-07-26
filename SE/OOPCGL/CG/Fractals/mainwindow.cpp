#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QLabel>
#include <QImage>

QImage img(600, 600, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    kochCurve(150, 360, 300, 100, 3);
    kochCurve(300, 100, 450, 360, 3);
    kochCurve(450, 360, 150, 360, 3);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}


// dda line drawing algo
void MainWindow::drawLine(int x1, int y1, int x2, int y2, QRgb val) {
    float xinc, yinc, dx, dy, x, y;
    int steps;
    dx = x2-x1;
    dy = y2-y1;

    if (abs(dx)>=abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xinc = dx/steps;
    yinc = dy/steps;

    x = x1;
    y = y1;
    for (int i=0; i<steps; i++) {
        img.setPixel(x, y, val);
        x+=xinc;
        y+=yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::kochCurve(int x1, int y1, int x2, int y2, int n) {
    int xa, ya, xb, yb, xmid, ymid;
    float theta = 3.14/3;

    QRgb white = qRgb(255, 255, 255);

    xa = ((2*x1)+x2)/3;
    ya = ((2*y1)+y2)/3;
    xb = (x1+(2*x2))/3;
    yb = (y1+(2*y2))/3;

    xmid = xa + (xb-xa)*cos(theta) + (yb-ya)*sin(theta);
    ymid = ya - (xb-xa)*sin(theta) + (yb-ya)*cos(theta);

    if (n>0) {
        kochCurve(x1, y1, xa, ya, n-1);
        kochCurve(xa, ya, xmid, ymid, n-1);
        kochCurve(xmid, ymid, xb, yb, n-1);
        kochCurve(xb, yb, x2, y2, n-1);
    }
    else {
        drawLine(x1, y1, xa, ya, white);
        drawLine(xa, ya, xmid, ymid, white);
        drawLine(xb, yb, xmid, ymid, white);
        drawLine(xb, yb, x2, y2, white);
    }
}
