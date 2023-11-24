#include "simulatedscenarios.h"

SimulatedScenarios::SimulatedScenarios()
{
    CPRfeedback *cprFb;
    VisualPrompts *display;
    arrhythmiadetection *detection;

    adultPads = false;
    pediatricPads = false;
    lowBattery = false;
}


void SimulatedScenarios::setAdultPads(bool b){adultPads = b;}
void SimulatedScenarios::setPediatricPads(bool b){adultPads = b;}
void SimulatedScenarios::setLowBattery(bool b){adultPads = b;}


void SimulatedScenarios::pediatric(){
    updateLCD(display->pediatricPads());
    startProcedure();
}

void SimulatedScenarios::adult(){
    updateLCD(display->adultPads());
    startProcedure();

}


void SimulatedScenarios::startProcedure(){



}

void SimulatedScenarios::batteryTest(){
    updateLCD(display->changeBatteries());
    delay(1);
    updateLCD(display->ifNewBattiesPressButton());
}

void SimulatedScenarios::selfTest(){

    //50-50 chance to work and fail

    if(lowBattery == true){
        batteryTest();
    }

    if(adultPads == true){
        updateLCD(display->unitOk());
        delay(1);
        adult();

    }else if(pediatricPads == true){
        updateLCD(display->unitOk());
        delay(1);
        pediatric();

    }else{

        updateLCD(display->plugInCable());

    }
}
