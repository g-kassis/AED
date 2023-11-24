#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),Scenarios()
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeElapsed()));

    //Buttons on AED
    connect(ui->powerButton, SIGNAL(clicked()), this, SLOT(onPowerButtonClicked()));
    connect(ui->shockButton, SIGNAL(clicked()), this, SLOT(onShockButtonClicked()));

    //Simulated Scenarios RadioButtons & checkBoxes
    connect(ui->adultCheckBox, SIGNAL(clicked()), this, SLOT(onCheckBox()));
    connect(ui->childCheckBox, SIGNAL(clicked()), this, SLOT(onCheckBox()));


    //User Interaction Buttons


    //Connect signals from simulatedScenarios
    connect(&Scenarios, SIGNAL(updateLCD(QString)), this, SLOT(handleVisualandVoice(QString)));
    connect(&Scenarios, SIGNAL(delay(int)), this, SLOT(delay(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onPowerButtonClicked(){
    //checks if a Simulated Scenario has been chosen
    if(ui->normalOperationScenarioButton->isChecked()){
        qInfo("normal ops");
    }else if(ui->badECGrythmButton->isChecked()){
        qInfo("bad ecg");
    }else if(ui->lowBatteryScenarioButton->isChecked()){
        qInfo("low battery");
    }else{
        qInfo("no simulated scenario selected");
    }
    //qInfo("Power Button Clicked");
//    min = 0;

//    ui->child_LED->hide();
//    ui->ok_LED->hide();
//    ui->ambulance_LED->hide();
//    ui->pads_LED->hide();
//    ui->clear_LED->hide();
//    ui->compressions_LED->hide();
//    ui->shock_LED->hide();

//    //self test (check batteries, check LEDs...)
//    ui->child_LED->show();
//    delay(1);
//    ui->child_LED->hide();

//    ui->ok_LED->show();
//    delay(1);
//    ui->ok_LED->hide();

//    ui->ambulance_LED->show();
//    delay(1);
//    ui->ambulance_LED->hide();

//    ui->pads_LED->show();
//    delay(1);
//    ui->pads_LED->hide();

//    ui->clear_LED->show();
//    delay(1);
//    ui->clear_LED->hide();


//    ui->compressions_LED->show();
//    delay(1);
//    ui->compressions_LED->hide();

//    ui->shock_LED->show();
//    delay(1);
//    ui->shock_LED->hide();
//    ui->statusIndicator->setPixmap(QPixmap(":/Images/greenCheck.jpg"));

//    Scenarios.selfTest();

//    timer->start(1000);
//    elapsedtimer.start();





}

//when power button is held >5 seconds
//initiates self test
void MainWindow::onPowerButtonHeld(){
    qInfo("Power Button Held for >5 seconds");
    qInfo("Initiating self test...");

    //self test


}

void MainWindow::onShockButtonClicked(){
    qInfo("Shock Button Clicked");


}

void MainWindow::onCheckBox(){
    if(ui->adultCheckBox->isChecked()){
        ui->childCheckBox->setCheckable(false);
        //Child_LED off
        ui->child_LED->hide();
        Scenarios.setAdultPads(true);

    }else if(ui->childCheckBox->isChecked()){
        ui->adultCheckBox->setCheckable(false);
        //Child_LED illuminate
        ui->child_LED->show();
        Scenarios.setPediatricPads(true);

    }else{
        ui->childCheckBox->setCheckable(true);
        ui->adultCheckBox->setCheckable(true);
        ui->child_LED->hide();

        Scenarios.setAdultPads(false);
        Scenarios.setPediatricPads(false);

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
