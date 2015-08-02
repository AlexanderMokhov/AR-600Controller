#pragma once
#include <iostream>
#include <map>
#include <mutex>
#include <stdlib.h>
#include <ADefinition.h>

class BufferReceive
{
private:
    char mRAW [1472];
    std::mutex mLocker;
    DeviceData mMotorData[71];
public:
    BufferReceive(void);
    ~BufferReceive(void);

    void Init(const char RAW_other[]);
    //добавить номер номер устройства в отправляемый буфер
    void SetDeviceChannel(short NumberDevice, short NumberChannel);
    void SetMotorReverce(short Number, bool value);

    short GetSensorYaw(short Number);//получить данные с сенсора рысканья
    short GetSensorPitch(short Number);
    short GetSensorRoll(short Number);//получить данные с сенсора вращения/крена
    short GetSensorUCH0(short Number);
    short GetSensorUCH1(short Number);
    short GetSensorUCH2(short Number);
    short GetSensorUCH3(short Number);
    short GetSensorTX(short Number);
    short GetSensorTY(short Number);
    short GetSensorFZ(short Number);
    short GetSensorValue(short Number,int Param);

    short GetMotorI(short Number);//получить ток мотора
    short GetMotorU(short Number);//получить напряжение мотора
    short GetMotorAngle(short Number);//получить текущую позицию мотора
    short GetMotorStiff(short Number);//получить KP
    short GetMotorDamp(short Number);//получить KI
    short GetMotorStatus(short Number);//получить статус мотора
    short GetMotorMinAngle(short Number);//получить минимальную позицию мотора
    short GetMotorMaxAngle(short Number);//получить максималную позицию мотора

    float GetPowerU61();
    float GetPowerU62();
    float GetPowerU81();
    float GetPowerU82();
    float GetPowerU48();
    float GetPowerU12();

    float GetPowerI61();
    float GetPowerI62();
    float GetPowerI81();
    float GetPowerI82();
    float GetPowerI48();
    float GetPowerI12();

    const char *GetRAW();
    std::mutex *GetLocker();
};

