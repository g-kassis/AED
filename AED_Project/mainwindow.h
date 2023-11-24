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
#include <QString>

#include "simulatedscenarios.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onPowerButtonClicked();
    void onShockButtonClicked();
    void onPowerButtonHeld();
    void timeElapsed();
    void onCheckBox();
    void delay(int);

    //handle functions
    void handleVisualandVoice(QString);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QElapsedTimer elapsedtimer;
    SimulatedScenarios Scenarios;
    int min;
};
#endif // MAINWINDOW_H
