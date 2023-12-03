#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),Scenarios()
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeElapsed()));

    //setup for ECG graph
    ui->ECGwave->addGraph();
    ui->ECGwave->setBackground(QColor(122, 129, 129));

    ui->ECGwave->xAxis->setLabel("Time");
    ui->ECGwave->xAxis->setRange(0,10);

    ui->ECGwave->yAxis->setLabel("Voltage");
    ui->ECGwave->yAxis->setRange(-2.5,2.5);


    //Buttons on AED
    connect(ui->powerButton, SIGNAL(clicked()), this, SLOT(onPowerButtonClicked()));
    connect(ui->shockButton, SIGNAL(clicked()), this, SLOT(onShockButtonClicked()));

    //Simulated Scenarios RadioButtons & checkBoxes
    connect(ui->adultCheckBox, SIGNAL(clicked()), this, SLOT(onCheckBox()));
    connect(ui->childCheckBox, SIGNAL(clicked()), this, SLOT(onCheckBox()));


    //User Interaction Buttons
    connect(ui->batteryResetButton, SIGNAL(clicked()), this, SLOT(onBatteryReset()));
    connect(ui->electrodeButton, SIGNAL(clicked()), this, SLOT(onPlaceElectrode()));
    connect(ui->cprButton, SIGNAL(clicked()), this, SLOT(onCPRinitiation()));

    //Connect signals from simulatedScenarios
    connect(&Scenarios, SIGNAL(updateLCD(QString)), this, SLOT(handleVisualandVoice(QString)));
    connect(&Scenarios, SIGNAL(updateLEDs(int)), this, SLOT(handleLEDs(int)));
    connect(&Scenarios, SIGNAL(updateNumShocks(int)), this, SLOT(handleNumShocks(int)));
    connect(&Scenarios, SIGNAL(delay(int)), this, SLOT(delay(int)));
    connect(&Scenarios, SIGNAL(updateECG(QVector<QPair<double,double>>)), this, SLOT(handleECG(QVector<QPair<double,double>>)));
    connect(&Scenarios, SIGNAL(continueRhythm(QVector<QPair<double,double>>*)), this, SLOT(handleContinueRhythm(QVector<QPair<double,double>>*)));
    connect(&Scenarios, SIGNAL(updateIndicator(int)), this, SLOT(handleIndicator(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onPowerButtonClicked(){
    qInfo("Power Button Clicked");

    //checks if a Simulated Scenario has been chosen
    if(ui->shockableScenario->isChecked()){
        qInfo("Shockable ECG");
        Scenarios.setLowBattery(false);
    }else if(ui->nonShockableScenario->isChecked()){
        qInfo("non-shock ECG");
        Scenarios.setLowBattery(false);
    }else if(ui->lowBatteryScenarioButton->isChecked()){
        qInfo("low battery");
        Scenarios.setLowBattery(true);
    }else{
        qInfo("no simulated scenario selected");
        return;
    }

    min = 0;

    ui->numberOfShocks->setText("SHOCKS: 0");

    ui->child_LED->hide();
    ui->ok_LED->hide();
    ui->ambulance_LED->hide();
    ui->pads_LED->hide();
    ui->clear_LED->hide();
    ui->compressions_LED->hide();
    ui->shock_LED->hide();

    //self test (check batteries, check LEDs...)
    Scenarios.selfTest();


    timer->start(1000);
    elapsedtimer.start();

    //waits for user to choose if patient is adult or pediatric (if they haven't already)
    if(Scenarios.getBatterySensor() == true){
        //don't do anything
    }
    else if(!ui->adultCheckBox->isChecked() && !ui->childCheckBox->isChecked()){
        eventLoop.exec();
        Scenarios.adult();
        Scenarios.pediatric();
    }

    //waits for operator to place pads on patient
    if(Scenarios.getBatterySensor() == false){
        handleIndicator(1);
        while(!Scenarios.getElectrodeSensor()){
            delay(1);
            Scenarios.startProcedure();
        }

        //checks if schockable or non-shockable rhythm
        if(ui->nonShockableScenario->isChecked()){
            Scenarios.startAnalysis(0); //non-shockable scenario
        }else{
            Scenarios.startAnalysis(1); //shockable scenario
        }

    }else{
        handleIndicator(0);
        ui->lcd->hide();
        ui->statusIndicator->hide();
        ui->mainInterface->setPixmap(QPixmap(":/Images/AED_Battery.jpg"));
    }


}

//when power button is held >5 seconds
//initiates self test
void MainWindow::onPowerButtonHeld(){
    qInfo("Power Button Held for >5 seconds");
    qInfo("Initiating self test...");

    //self test
    Scenarios.selfTest();

}

void MainWindow::onShockButtonClicked(){
    qInfo("Shock Button Clicked");
    Scenarios.deliverShock();
}

void MainWindow::handleNumShocks(int n){
    ui->numberOfShocks->setText("SHOCKS: " + QString::number(n));
}

void MainWindow::onPlaceElectrode(){
    qInfo("electrode placed");
    Scenarios.setElectrodeSensor(true);


}

void MainWindow::onCPRinitiation(){
    Scenarios.CPRprocedure();
}

void MainWindow::onCallForHelp(){

}

void MainWindow::onBatteryReset(){
    qInfo("Battery Reset clicked");
    ui->shockableScenario->setChecked(true);
    Scenarios.setLowBattery(false);
    ui->mainInterface->setPixmap(QPixmap(":/Images/3004project.jpg"));
    ui->lcd->show();
    ui->statusIndicator->show();


}

void MainWindow::onCheckBox(){
    if(ui->adultCheckBox->isChecked()){
        ui->childCheckBox->setCheckable(false);
        //Child_LED off
        ui->child_LED->hide();
        Scenarios.setAdultPads(true);
        eventLoop.quit();

    }else if(ui->childCheckBox->isChecked()){
        ui->adultCheckBox->setCheckable(false);
        //Child_LED illuminate
        ui->child_LED->show();
        Scenarios.setPediatricPads(true);
        eventLoop.quit();

    }else{
        ui->childCheckBox->setCheckable(true);
        ui->adultCheckBox->setCheckable(true);
        ui->child_LED->hide();

        Scenarios.setAdultPads(false);
        Scenarios.setPediatricPads(false);

    }

}


//LED Control function (only handles LEDS)
void MainWindow::handleLEDs(int pictogramID){
    if(pictogramID == 0){   //self test case (LED test check)
        ui->child_LED->show();
        delay(1);
        ui->child_LED->hide();
        ui->ok_LED->show();
        delay(1);
        ui->ok_LED->hide();
        ui->ambulance_LED->show();
        delay(1);
        ui->ambulance_LED->hide();
        ui->pads_LED->show();
        delay(1);
        ui->pads_LED->hide();
        ui->clear_LED->show();
        delay(1);
        ui->clear_LED->hide();
        ui->compressions_LED->show();
        delay(1);
        ui->compressions_LED->hide();
        ui->shock_LED->show();
        delay(1);
        ui->shock_LED->hide();
        if(ui->childCheckBox->isChecked()){ //pediatric pads
            ui->child_LED->show();
        }

    }else{  //other cases

        if(pictogramID == 1){   //Responsiveness LED
            //Turn off other LEDS
            ui->ambulance_LED->hide();
            ui->pads_LED->hide();
            ui->clear_LED->hide();
            ui->compressions_LED->hide();
            ui->shock_LED->hide();

            ui->ok_LED->show();

        }else if(pictogramID == 2){ //Help LED
            //Turn off other LEDS
            ui->ok_LED->hide();
            ui->pads_LED->hide();
            ui->clear_LED->hide();
            ui->compressions_LED->hide();
            ui->shock_LED->hide();

            ui->ambulance_LED->show();

        }else if(pictogramID == 3){ //Place pads LED
            //Turn off other LEDS
            ui->ok_LED->hide();
            ui->ambulance_LED->hide();
            ui->clear_LED->hide();
            ui->compressions_LED->hide();
            ui->shock_LED->hide();

            ui->pads_LED->show();

        }else if(pictogramID == 4){ //Clear LED
            //Turn off other LEDS
            ui->ok_LED->hide();
            ui->ambulance_LED->hide();
            ui->pads_LED->hide();
            ui->compressions_LED->hide();
            ui->shock_LED->hide();

            ui->clear_LED->show();

        }else if(pictogramID == 5){ //CPR LED
            //Turn off other LEDS
            ui->ok_LED->hide();
            ui->ambulance_LED->hide();
            ui->pads_LED->hide();
            ui->clear_LED->hide();
            ui->shock_LED->hide();

            ui->compressions_LED->show();

        }else{  //shock LED
            //Turn off other LEDS
            ui->ok_LED->hide();
            ui->ambulance_LED->hide();
            ui->pads_LED->hide();
            ui->compressions_LED->hide();

            ui->clear_LED->show();
            ui->shock_LED->show();

        }


    }
}

//updates the ECG waveform based on what rhythm is detected (plots the original first wave)
void MainWindow::handleECG(QVector<QPair<double,double>> ECGdata){
    qInfo("graphing...");
    for(int i = 0; i < ECGdata.size(); i++){

        ui->ECGwave->replot();
        ui->ECGwave->graph(0)->addData(ECGdata.at(i).first,ECGdata.at(i).second);
        ui->ECGwave->replot();

    }

}

//updates the graph (continues plots the original first wave)
void MainWindow::handleContinueRhythm(QVector<QPair<double,double>> *ECGdata){
    qInfo("continue graphing...");
    double delta;
    if(ui->shockableScenario->isChecked()){
        delta = 0.9375;
    }else{
        delta = 2;

    }

    for(int i = 0; i < ECGdata->size(); i++){

        ui->ECGwave->replot();
        (*ECGdata)[i] = qMakePair((*ECGdata)[i].first + delta, (*ECGdata)[i].second);
        if((*ECGdata)[i].first > ui->ECGwave->xAxis->range().upper){
            ui->ECGwave->xAxis->setRange(ui->ECGwave->xAxis->range().lower + 10,ui->ECGwave->xAxis->range().upper + 10);
        }
        ui->ECGwave->graph(0)->addData(ECGdata->at(i).first,ECGdata->at(i).second);
        ui->ECGwave->replot();

    }
}

void MainWindow::handleIndicator(int indicator){
    if(indicator == 0){
        ui->statusIndicator->setPixmap(QPixmap(":/Images/redX.jpg"));
    }else{
        ui->statusIndicator->setPixmap(QPixmap(":/Images/greenCheck.jpg"));
    }
}

void MainWindow::handleVisualandVoice(QString str){
    ui->visualPrompt->setText(str);
}

void MainWindow::timeElapsed(){
    if((elapsedtimer.elapsed()/1000) % 60 == 0 && elapsedtimer.elapsed()/1000 != 0 ){
        elapsedtimer.restart();
        min += 1;
        //qDebug()<<"time elapsed: "<<min<<":"<<elapsedtimer.elapsed()/1000;
        if(min > 9){
            //qDebug()<<"time elapsed: 0"<<min<<":0"<<elapsedtimer.elapsed()/1000;
            ui->elapsedTime->setText((std::to_string(min)+":0"+std::to_string(elapsedtimer.elapsed()/1000)).c_str());
        }else{
            //qDebug()<<"time elapsed: 0"<<min<<":"<<elapsedtimer.elapsed()/1000;
            ui->elapsedTime->setText(("0"+std::to_string(min)+":0"+std::to_string(elapsedtimer.elapsed()/1000)).c_str());
        }
    }else if(min >= 0 && min <= 99){
        if(min >= 0 && min <= 9){
            if(elapsedtimer.elapsed()/1000 <= 9){
                //qDebug()<<"time elapsed: 0"<<min<<":0"<<elapsedtimer.elapsed()/1000;
                ui->elapsedTime->setText(("0"+std::to_string(min)+":0"+std::to_string(elapsedtimer.elapsed()/1000)).c_str());
            }else{
                //qDebug()<<"time elapsed: 0"<<min<<":"<<elapsedtimer.elapsed()/1000;
                ui->elapsedTime->setText(("0"+std::to_string(min)+":"+std::to_string(elapsedtimer.elapsed()/1000)).c_str());
            }

        }else{
            if(elapsedtimer.elapsed()/1000 <= 9){
                //qDebug()<<"time elapsed: "<<min<<":0"<<elapsedtimer.elapsed()/1000;
                ui->elapsedTime->setText((std::to_string(min)+":0"+std::to_string(elapsedtimer.elapsed()/1000)).c_str());
            }else{
                //qDebug()<<"time elapsed: "<<min<<":"<<elapsedtimer.elapsed()/1000;
                ui->elapsedTime->setText((std::to_string(min)+":"+std::to_string(elapsedtimer.elapsed()/1000)).c_str());
            }
        }

    }else if(min == 99){
        elapsedtimer.restart();
    }
}

void MainWindow::delay(int second){
    QTime dieTime= QTime::currentTime().addSecs(second);
    while (QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
