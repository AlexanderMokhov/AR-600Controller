#ifndef ADEFINITION
#define ADEFINITION

typedef unsigned char BYTE;

struct DeviceData
{
    bool isReverce; //Реверс
    short MinAngle; //Минимальный угол
    short MaxAngle; //Максимальный угол
    bool isEnable;  //Доступность
    short Channel;  //Номер канала
};

#endif // ADEFINITION

