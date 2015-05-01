#ifndef FOOTSENSOR_H
#define FOOTSENSOR_H

#include "Device.h"

//Класс сенсора стопы
class FootSensor : public Device
{
private:
    int             mUCH0;//мост 0
    int             mUCH1;//мост 1
    bool            mUCH2;//мост 2
    int             mUCH3;//мост 3
    int             mMomentX;//Момент по X
    int             mMomentY;//Момент по Y
    int             mPowerZ;//Сила по Z

public:
    FootSensor();
    ~FootSensor();

    FootSensor(unsigned int Number,
               unsigned int NumberBuffer,
               std::string Name,
               int UCH0,
               int UCH1,
               int UCH2,
               int UCH3);

    int GetUCH0();
    int GetUCH1();
    int GetUCH2();
    int GetUCH3();

    void SetUCH0(int UCH);
    void SetUCH1(int UCH);
    void SetUCH2(int UCH);
    void SetUCH3(int UCH);
};

#endif // FOOTSENSOR_H
