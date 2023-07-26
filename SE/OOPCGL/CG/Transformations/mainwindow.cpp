#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
/*
https://github.com/IamVaibhavsar/Second_Year_Lab_Assignments/blob/master/Computer%20Graphics%20Lab/2DTransformation/2DTransformation.cpp
*/

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

QImage img(600, 600, QImage::Format_RGB888);

int MainWindow::xcor[] = {300, 375, 450, 375, 300};
int MainWindow::ycor[] = {300, 225, 300, 375, 300};

// bresenham line drawing algo
void MainWindow::drawLine(int x1, int y1, int x2, int y2, char c) {
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
        if (c=='W')
            img.setPixel(x, y, qRgb(255, 255, 255));
        else if (c=='R')
            img.setPixel(x, y, qRgb(255, 0, 0));
        else if (c=='B')
            img.setPixel(x, y, qRgb(0, 0, 255));
        else if (c=='C')
            img.setPixel(x, y, qRgb(0, 255, 255));
        else if (c=='V')
            img.setPixel(x, y, qRgb(255, 0, 255));
        x+=xinc;
        y+=yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::translation(int x[], int y[], int tx, int ty) {
    int x1, y1, x2, y2;
    x1 = x[0]+tx;
    y1 = y[0]+ty;
    for (int i=1; i<5; i++) {
        x2 = x[i]+tx;
        y2 = y[i]+ty;
        drawLine(x1, y1, x2, y2, 'B');
        x1 = x2;
        y1 = y2;
    }
}


void MainWindow::scaling(int x[], int y[], float sx, float sy) {
    int x1, y1, x2, y2;
    for (int i=0; i<4; i++) {
        x1 = ((x[i]-300)*sx) + 300;
        y1 = ((300-y[i])*sy) + 300;
        x2 = ((x[i+1]-300)*sx) + 300;
        y2 = ((300-y[i+1])*sy) + 300;
        drawLine(x1, y1, x2, y2, 'V');
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::rotation(int x[], int y[], float theta) {
    float a;
    int x1, y1, x2, y2;

    a = (theta*3.14)/180;
    for (int i=0; i<4; i++) {
        x1 = (cos(a)*(x[i]-300)) - (sin(a)*(300-y[i]));
        y1 = (sin(a)*(x[i]-300)) + (cos(a)*(300-y[i]));
        x2 = (cos(a)*(x[i+1]-300)) - (sin(a)*(300-y[i+1]));
        y2 = (sin(a)*(x[i+1]-300)) + (cos(a)*(300-y[i+1]));
        drawLine(x1+300, y1+300, x2+300, y2+300, 'C');
    }
}


// DRAW button
void MainWindow::on_pushButton_3_clicked()
{
    // ORIGIN = (300, 300)
    drawLine(300, 0, 300, 600, 'R');
    drawLine(0, 300, 600, 300, 'R');

    // rhombus
    drawLine(300, 300, 375, 225, 'W');
    drawLine(375, 225, 450, 300, 'W');
    drawLine(450, 300, 375, 375, 'W');
    drawLine(375, 375, 300, 300, 'W');
}


// TRANSLATE button
void MainWindow::on_pushButton_clicked()
{
    int tx = ui->textEdit->toPlainText().toInt();
    int ty = ui->textEdit_2->toPlainText().toInt();
    translation(xcor, ycor, tx, ty);
}


// SCALE button
void MainWindow::on_pushButton_2_clicked()
{
    float sx = ui->textEdit_3->toPlainText().toFloat();
    float sy = ui->textEdit_4->toPlainText().toFloat();
    scaling(xcor, ycor, sx, sy);
}


// ROTATE button
void MainWindow::on_pushButton_4_clicked()
{
    float th = ui->textEdit_5->toPlainText().toFloat();
    rotation(xcor, ycor, th);
}
