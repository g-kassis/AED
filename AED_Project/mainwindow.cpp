#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->powerButton, SIGNAL(clicked()), this, SLOT(onPowerButtonClicked()));
    connect(ui->shockButton, SIGNAL(clicked()), this, SLOT(onShockButtonClicked()));
    connect(ui->adultCheckBox, SIGNAL(clicked()), this, SLOT(onCheckBox()));
    connect(ui->childCheckBox, SIGNAL(clicked()), this, SLOT(onCheckBox()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onPowerButtonClicked(){
    qInfo("Power Button Clicked");

    //self test
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

    }else if(ui->childCheckBox->isChecked()){
        ui->adultCheckBox->setCheckable(false);
        //Child_LED illuminate

    }else{
        ui->childCheckBox->setCheckable(true);
        ui->adultCheckBox->setCheckable(true);
    }
}

//void MainWindow::onpadsbutton(){
//    if(!ui->adultCheckBox->isChecked() && !ui->childCheckBox->isChecked()){
//        qInfo("Select Type of pads first");
//        return;
//    }

//}
