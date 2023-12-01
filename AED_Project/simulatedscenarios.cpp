#include "simulatedscenarios.h"

SimulatedScenarios::SimulatedScenarios()
{
    cprFb = new CPRfeedback;
    display = new VisualPrompts;
    detection = new arrhythmiadetection;

    adultPads = false;
    pediatricPads = false;
    lowBattery = false;
    electrodeSensor = false;

    ECGdata = new QVector<QPair<double, double>>;
}


void SimulatedScenarios::setAdultPads(bool b){adultPads = b;}
void SimulatedScenarios::setPediatricPads(bool b){pediatricPads = b;}
void SimulatedScenarios::setLowBattery(bool b){lowBattery = b;}
void SimulatedScenarios::setElectrodeSensor(bool b){electrodeSensor = b;}
bool SimulatedScenarios::getElectrodeSensor(){return electrodeSensor;}
bool SimulatedScenarios::getBatterySensor(){return lowBattery;}


//After the Fully Automatic AED Plus is powered on and completes its self-test, the unit will issue
//an “Adult Pads” voice prompt or a “Pediatric Pads” voice prompt to indicate the type of electrodes
//connected to the unit.
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



//When the Fully Automatic AED Plus has completed its self test, the unit automatically initiates the sequence of
//voice prompts and graphic illuminations for a rescue event
//by cycling through the check responsivness, call for help and attach pads to patient sequence
//next function: startAnalysis()
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

//As soon as electrodes are attached to the victim and impedance of the connection is
//verified, the unit stops cycling through the check responsivness, call for help and attach pads to patient sequence
//and automatically begins analysis of the ECG rhythm
void SimulatedScenarios::startAnalysis(int shock){
    //warns operator to not move patient
    updateLCD(display->dontTouchPatient());
    updateLEDs(4);

    delay(5); //analysis delay

    //arrhythmia detection
    int randomECG = QRandomGenerator::global()->bounded(1,3); //50% chance between vTach and vFib
    ECGtimer = new QTimer(this);

    if(shock == 1){   //if user selected shockable then it randomizes between vTach and vFib rhythms

        if(randomECG == 1){   //vTach
            ECGdata = detection->ventricularTach();
            updateECG(*detection->ventricularTach());

        }else{                //vFib
            ECGdata = detection->ventricularFib();
            updateECG(*detection->ventricularFib());

        }

    }else{   //if user selected non-shockable (normal ECG rhythm)

        ECGdata = detection->nonShockable();
        updateECG(*detection->nonShockable());

    }


    connect(ECGtimer, SIGNAL(timeout()), this, SLOT(newValues()));
    ECGtimer->start(5000);

}

void SimulatedScenarios::batteryTest(){
    updateLCD(display->changeBatteries());
    delay(1);
    updateLCD(display->ifNewBattiesPressButton());
}



//The Fully Automatic AED Plus performs a self test whenever the unit is turned on and verifies the
//following functions:
//1. Battery Capacity: Verifies that the battery usage indicator shows adequate battery capacity
//remaining.
//2. Defibrillation Electrodes Connection: Verifies that the defibrillation electrodes are properly pre-
//connected to the device
//next function: startProcedure();
void SimulatedScenarios::selfTest(){

    updateLEDs(0);
    if(lowBattery == true){
        batteryTest();
    }else{

        if(adultPads == true){
            updateLCD(display->unitOk());
            updateIndicator(1);
            delay(1);
            adult();

        }else if(pediatricPads == true){
            updateLCD(display->unitOk());
            updateIndicator(1);
            delay(1);
            pediatric();

        }else{
            //If the electrode cable is not properly
            //attached to the unit, the unit issues the PLUG IN CABLE prompt
            updateLCD(display->plugInCable());

        }
    }

}

//sends updated ECG rhythm values
void SimulatedScenarios::newValues(){
    continueRhythm(ECGdata);
}
