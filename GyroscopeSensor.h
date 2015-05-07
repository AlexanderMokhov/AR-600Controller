#ifndef GYROSCOPESENSOR_H
#define GYROSCOPESENSOR_H

#include "Device.h"

//Класс сенсора - гироскопа
class GyroscopeSensor : public Device
{
private:
    int             mYAW;//рысканье
    int             mPITCH;//тангаж
    bool            mROLL;//крен

public:
    GyroscopeSensor();
    ~GyroscopeSensor();
    GyroscopeSensor(unsigned int Number,
                    unsigned int NumberBuffer,
                    std::string Name);

    int GetYAW();
    int GetPITCH();
    int GetROLL();

    void SetYAW(int YAW);
    void SetPITH(int PITCH);
    void SetROLL(int ROLL);
};

#endif // GYROSCOPESENSOR_H
