#ifndef ADEFINITION
#define ADEFINITION

typedef unsigned char BYTE;

struct DeviceData
{
    bool isReverce; //Реверс
    short MinAngle; //Минимальный угол
    short MaxAngle; //Максимальный угол
    bool isEnable;  //Используется
    short Channel;  //Номер канала
};

#endif // ADEFINITION

