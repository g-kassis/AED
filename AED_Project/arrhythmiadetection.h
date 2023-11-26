#ifndef ARRHYTHMIADETECTION_H
#define ARRHYTHMIADETECTION_H

#include <QObject>

class arrhythmiadetection : public QObject
{
    Q_OBJECT
public:
    arrhythmiadetection();

    void setVfib(bool rythm);
    void setVtach(bool rythm);

    void ventricularTach();
    void ventricularFib();
    void nonShockable();

private:
    bool vTach;
    bool vFib;
};

#endif // ARRHYTHMIADETECTION_H
