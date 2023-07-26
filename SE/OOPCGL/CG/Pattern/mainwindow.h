#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void draw_line(int, int, int, int);
    void draw_circle(int, int, int);
    void fig_1();
    void fig_2();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
