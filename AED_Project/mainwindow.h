#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <stdio.h>
#include <stdlib.h>
#include <QMainWindow>
#include <QCheckBox>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QCoreApplication>
#include <QEventLoop>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void delay(int);

public slots:
    void onPowerButtonClicked();
    void onShockButtonClicked();
    void onPowerButtonHeld();
    void timeElapsed();
    void onCheckBox();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QElapsedTimer elapsedtimer;
    int min;
};
#endif // MAINWINDOW_H
