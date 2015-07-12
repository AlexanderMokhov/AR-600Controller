#pragma once
#include <iostream>
#include <map>
#include <mutex>
#include <stdlib.h>
#include <ADefinition.h>

class WriteBuffer
{
private:
    char mRAW [1472];//массив сырых данных
    std::mutex mLocker;//мьютекс
    DeviceData mMotorData[71];
public:
    WriteBuffer(void);
    ~WriteBuffer(void);

    //инициализация
    void Init(unsigned char RAW_other[]);
    void Init(void);
    const char *GetRAW();
    int GetSize(){return 1472;}

	//датчик усилия
    void SetSensorUCH0(short Number, short value);
    void SetSensorUCH1(short Number, short value);
    void SetSensorUCH2(short Number, short value);
    void SetSensorUCH3(short Number, short value);

    //управление моторами
    void SetMotorAngle(short Number, short value);
    void SetMotorCalibration(short Number, short value);
    void SetMotorStiff(short Number, short value);//установить KP
    void SetMotorDump(short Number, short value);//установить KI
    void SetMotorTorque(short Number, short value);//установить KD
    void SetMotorMinAngle(short Number, short value);
    void SetMotorMaxAngle(short Number, short value);
    void SetMotorEnable(short Number, bool value);
    void SetMotorReverce(short Number, bool value);

    short GetMotorTorque(short Number);
    //изменение состояния мотора
    void MotorStop(short Number);//динамическое торможение
    void MotorTrace(short Number);//режим следование за положением
    void MotorRelax(short Number);//убрать фиксацию мотора
    void MotorStopBrake(short Number);//режим фиксации

    //управление питанием
    void PowerOn61(void);
    void PowerOn62(void);
    void PowerOn81(void);
    void PowerOn82(void);
    void PowerOn12(void);
    void PowerOn48(void);

    void PowerOff61(void);
    void PowerOff62(void);
    void PowerOff81(void);
    void PowerOff82(void);
    void PowerOff12(void);
    void PowerOff48(void);

    //управление звуком
    void MuteOn(void);
    void MuteOff(void);

    //добавить номер номер устройства в отправляемый буфер
    void SetDeviceChannel(short NumberDevice, short NumberChannel);

    std::mutex *GetLocker();

};

