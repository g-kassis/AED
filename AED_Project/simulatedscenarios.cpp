#include "simulatedscenarios.h"

SimulatedScenarios::SimulatedScenarios()
{
    CPRfeedback *cprFb;
    VisualPrompts *display;
    arrhythmiadetection *detection;

    adultPads = false;
    pediatricPads = false;
    lowBattery = false;
    electrodeSensor = false;
}


void SimulatedScenarios::setAdultPads(bool b){adultPads = b;}
void SimulatedScenarios::setPediatricPads(bool b){pediatricPads = b;}
void SimulatedScenarios::setLowBattery(bool b){lowBattery = b;}
void SimulatedScenarios::setElectrodeSensor(bool b){electrodeSensor = b;}
bool SimulatedScenarios::getElectrodeSensor(){return electrodeSensor;}

void SimulatedScenarios::pediatric(){
    if(adultPads == true){return;}
    delay(1);
    updateLCD(display->pediatricPads());
    delay(1);
    startProcedure();
}

void SimulatedScenarios::adult(){
    if(pediatricPads == true){return;}
    delay(1);
    updateLCD(display->adultPads());
    delay(1);
    startProcedure();

}

void SimulatedScenarios::startAnalysis(){
    //warns operator to not move patient
    updateLCD(display->dontTouchPatient());
    updateLEDs(4);

    //arrhythmia detection

}

void SimulatedScenarios::startProcedure(){
    delay(1);

    //tells operator to stay calm
    updateLCD(display->stayCalm());
    delay(1);

    //check patient responsivness
    updateLCD(display->checkResponsivness());
    updateLEDs(1);
    delay(1);

    //call for help
    updateLCD(display->callForHelp());
    updateLEDs(2);
    delay(1);

    //attach defib pads to patient
    updateLCD(display->attchDefibPads());
    updateLEDs(3);
    delay(1);

}

void SimulatedScenarios::batteryTest(){
    updateLCD(display->changeBatteries());
    delay(1);
    updateLCD(display->ifNewBattiesPressButton());
}

void SimulatedScenarios::selfTest(){

    updateLEDs(0);
    //50-50 chance to work and fail
    if(lowBattery == true){
        batteryTest();
    }else{

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

}
