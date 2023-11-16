#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->powerButton, SIGNAL(clicked()), this, SLOT(onPowerButtonClicked()));
    connect(ui->shockButton, SIGNAL(clicked()), this, SLOT(onShockButtonClicked()));

    QImage *image = new QImage();
    image->load("E:/Resources/Images/3004project.png");
    image->save("E:/Qt/TestProject/Images/connect2.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onPowerButtonClicked(){
    qInfo("Power Button Clicked");
}

void MainWindow::onShockButtonClicked(){
    qInfo("Shock Button Clicked");
}
