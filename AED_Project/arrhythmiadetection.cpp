#include "arrhythmiadetection.h"


//Cardiac Arrhythmia Detection: AEDs can analyze the heart's electrical activity to determine if
//a shockable rhythm, such as ventricular fibrillation or ventricular tachycardia, is present. If such
//a rhythm is detected, the AED advises the user to deliver a shock.


arrhythmiadetection::arrhythmiadetection()
{
    vTach = false;
    vFib = false;
}

void arrhythmiadetection::setVtach(bool rythm){vTach = rythm;}
void arrhythmiadetection::setVfib(bool rythm){vFib = rythm;}


//detects Ventricular Tachycardia
QVector<QPair<double,double>> arrhythmiadetection::ventricularTach(){

    QVector<QPair<double, double>> data;
    data.append(qMakePair(0,0));
    data.append(qMakePair(0.25,-2.5));
    data.append(qMakePair(0.335,2.25));
    data.append(qMakePair(0.5,2.5));
    data.append(qMakePair(0.75,2));
    data.append(qMakePair(0.8125,1.5));
    data.append(qMakePair(0.9375,-2.25));
//    data.append(qMakePair(,));
//    data.append(qMakePair(,));
//    data.append(qMakePair(,));

    return data;
}

//detects Ventricular Tachycardia
QVector<QPair<double,double>> arrhythmiadetection::ventricularFib(){

    QVector<QPair<double, double>> data;
    data.append(qMakePair(0,0));
    data.append(qMakePair(2,-4));
    data.append(qMakePair(3,4));
    data.append(qMakePair(4,5));
    data.append(qMakePair(6,3));
    data.append(qMakePair(6.5,1));
    data.append(qMakePair(7.5,-3));

    return data;
}


//detects non shockable rythms
void arrhythmiadetection::nonShockable(){

}
