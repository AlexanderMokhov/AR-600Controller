#ifndef ADEFINITION
#define ADEFINITION

typedef unsigned char BYTE;

struct DeviceData
{
    bool isReverce; //Реверс
    short MinAngle; //Мин. угол
    short MaxAngle; //Макс. угол
    bool isEnable;  //Используется
    short Channel;  //Номер канала
};

#endif // ADEFINITION

