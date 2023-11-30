#ifndef SIMULATEDSCENARIOS_H
#define SIMULATEDSCENARIOS_H

#include <QObject>
#include <QString>
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
    void startAnalysis();
    void startProcedure();
    void batteryTest();
    void selfTest();

    //setter
    void setAdultPads(bool b);
    void setPediatricPads(bool);
    void setLowBattery(bool);
    void setElectrodeSensor(bool);

    bool getElectrodeSensor();

signals:
    void updateLCD(QString);
    void updateLEDs(int);
    void updateECG(int);
    void delay(int);

private:
    CPRfeedback *cprFb;
    VisualPrompts *display;
    arrhythmiadetection *detection;

    bool adultPads;
    bool pediatricPads;
    bool lowBattery;
    bool electrodeSensor;
};

#endif // SIMULATEDSCENARIOS_H
