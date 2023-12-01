#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <stdio.h>
#include <stdlib.h>
#include <QMainWindow>
#include <QCheckBox>
#include <QTime>
#include <QTimer>
#include <QVector2D>
#include <QColor>
#include <QDebug>
#include <QCoreApplication>
#include <QEventLoop>
#include <QElapsedTimer>
#include <QString>

#include "qcustomplot.h"
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

    //On AED functions
    void onPowerButtonClicked();
    void onShockButtonClicked();
    void onPowerButtonHeld();

    //simulated Scenario functions
    void onCheckBox();

    //User Interaction function
    void onPlaceElectrode();
    void onCPRinitiation();
    void onCallForHelp();
    void onBatteryReset();

    //handle functions
    void handleVisualandVoice(QString);
    void handleIndicator(int);
    void handleLEDs(int);
    void handleECG(QVector<QPair<double,double>>);

    //Extras
    void timeElapsed();
    void delay(int);


private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QElapsedTimer elapsedtimer;
    SimulatedScenarios Scenarios;
    QEventLoop eventLoop;
    QCustomPlot ECGgraph;
    int min;
};
#endif // MAINWINDOW_H
