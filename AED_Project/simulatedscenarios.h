#ifndef SIMULATEDSCENARIOS_H
#define SIMULATEDSCENARIOS_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QTime>
#include <QTimer>
#include <QPair>
#include <QRandomGenerator>
#include "cprfeedback.h"
#include "visualprompts.h"
#include "arrhythmiadetection.h"


class SimulatedScenarios : public QObject
{
    Q_OBJECT
public:
    SimulatedScenarios();

    void pediatric();
    void adult();
    void startAnalysis(int);
    void startProcedure();
    void deliverShock();
    void CPRprocedure();
    void batteryTest();
    void selfTest();

    //setter
    void setAdultPads(bool b);
    void setPediatricPads(bool);
    void setLowBattery(bool);
    void setElectrodeSensor(bool);

    bool getElectrodeSensor();
    bool getBatterySensor();


signals:
    void updateIndicator(int);
    void updateLCD(QString);
    void updateLEDs(int);
    void updateNumShocks(int);
    void updateECG(QVector<QPair<double,double>>);
    void continueRhythm(QVector<QPair<double,double>>*);
    void delay(int);

public slots:
    void newValues();


private:
    CPRfeedback *cprFb;
    VisualPrompts *display;
    arrhythmiadetection *detection;
    QTimer *ECGtimer;
    QVector<QPair<double,double>> *ECGdata;
    int numShocks;

    bool adultPads;
    bool pediatricPads;
    bool lowBattery;
    bool electrodeSensor;
};

#endif // SIMULATEDSCENARIOS_H
