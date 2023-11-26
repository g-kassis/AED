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
void arrhythmiadetection::ventricularTach(){

}

//detects Ventricular Tachycardia
void arrhythmiadetection::ventricularFib(){

}


//detects non shockable rythms
void arrhythmiadetection::nonShockable(){

}
