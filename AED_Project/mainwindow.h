#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onPowerButtonClicked();
    void onShockButtonClicked();
    void onPowerButtonHeld();
    void onCheckBox();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
