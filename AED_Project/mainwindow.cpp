#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);

    connect(ui->powerButton, SIGNAL(clicked()), this, SLOT(onPowerButtonClicked()));
    connect(ui->shockButton, SIGNAL(clicked()), this, SLOT(onShockButtonClicked()));
    connect(ui->adultCheckBox, SIGNAL(clicked()), this, SLOT(onCheckBox()));
    connect(ui->childCheckBox, SIGNAL(clicked()), this, SLOT(onCheckBox()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timeElapsed()));



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onPowerButtonClicked(){
    qInfo("Power Button Clicked");
    min = 0;
    timer->start(1000);
    elapsedtimer.start();

    ui->child_LED->hide();
    ui->ok_LED->hide();
    ui->ambulance_LED->hide();
    ui->pads_LED->hide();
    ui->clear_LED->hide();
    ui->compressions_LED->hide();
    ui->shock_LED->hide();

    //self test (check batteries, check LEDs...)
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

//    while(!ui->adultCheckBox->isChecked() && !ui->childCheckBox->isChecked()){
//        delay(1); //to allow user time to select type of pads
//        ui->statusIndicator->setPixmap(QPixmap(":/Images/redX.jpg"));
//        //Plug in cable voice and visual prompt



//    }

    ui->statusIndicator->setPixmap(QPixmap(":/Images/greenCheck.jpg"));

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

        //Adult pads voice and visual prompt

    }else if(ui->childCheckBox->isChecked()){
        ui->adultCheckBox->setCheckable(false);
        //Child_LED illuminate
        ui->child_LED->show();

        //Pediatric pads voice and visual prompt


    }else{
        ui->childCheckBox->setCheckable(true);
        ui->adultCheckBox->setCheckable(true);
        ui->child_LED->hide();

    }
}

//void MainWindow::onpadsbutton(){
//    if(!ui->adultCheckBox->isChecked() && !ui->childCheckBox->isChecked()){
//        qInfo("Select Type of pads first");
//        return;
//    }

//}

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
