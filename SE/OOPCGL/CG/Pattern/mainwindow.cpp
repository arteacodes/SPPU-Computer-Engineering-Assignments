#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage img(500,600, QImage::Format_RGB888);

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



void MainWindow::on_pushButton_clicked()
{
    fig_1();
    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_2_clicked()
{
    fig_2();
    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::fig_1(){
    //diamond
    draw_line(200,150, 300,100);
    draw_line(300,100, 400,150);
    draw_line(400,150, 300,200);
    draw_line(300,200, 200,150);

    draw_circle(300, 150, 44);

    //rectangle
    draw_line(200,100, 200,200);
    draw_line(200,200, 400,200);
    draw_line(400,200, 400,100);
    draw_line(400,100, 200,100);
}

void MainWindow::fig_2(){
    //triangle
    draw_line(200,500, 250,413);
    draw_line(250,413, 300,500);
    draw_line(300,500, 200,500);

    draw_circle(250, 471, 29);
    draw_circle(250, 471, 58);

}

// dda line algo
void MainWindow::draw_line(int x1, int y1, int x2, int y2){
    float xinc, yinc, dx, dy, x, y;
    dx = x2-x1;
    dy = y2-y1;
    int step = abs(dx)>abs(dy)? abs(dx):abs(dy);
    xinc = dx / step;
    yinc = dy / step;
    x = x1;
    y = y1;
    for(int i=0; i<step; i++){
        img.setPixel(x, y, qRgb(255, 255, 255));
        x += xinc;
        y += yinc;
    }
}


// bresenham line algo
void MainWindow::draw_circle(int xc, int yc, int r){
    int x1 = 0;
    int y1 = r;
    float dp = 3-(2*r);

    while(x1<=y1) {
        if (dp<=0)
            dp += (4*x1) + 6;
        else {
            dp += 4*(x1-y1) + 10;
            y1--;
        }
        x1++;

        img.setPixel(x1+xc, y1+yc, qRgb(255, 255, 255));
        img.setPixel(x1+xc, yc-y1, qRgb(255, 255, 255));
        img.setPixel(xc-x1, y1+yc, qRgb(255, 255, 255));
        img.setPixel(xc-x1, yc-y1, qRgb(255, 255, 255));
        img.setPixel(xc+y1, yc+x1, qRgb(255, 255, 255));
        img.setPixel(xc+y1, yc-x1, qRgb(255, 255, 255));
        img.setPixel(xc-y1, yc+x1, qRgb(255, 255, 255));
        img.setPixel(xc-y1, yc-x1, qRgb(255, 255, 255));
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
}


