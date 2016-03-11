#pragma once

#include <iostream>
#include <map>
#include <mutex>
#include <stdlib.h>

#include "BufferDefinition.h"

class BufferRecv
{
private:
    char m_RAW [bufferSize];
    std::mutex m_locker;
    deviceData m_motorsData[channelsNumber];

    int16_t readInt16(uint16_t address);
    float readFloat(uint16_t address);

public:
    BufferRecv(void);
    ~BufferRecv(void);

    void initialize( const char RAW_other[] );
    //добавить номер номер устройства в отправляемый буфер
    void setDeviceChannel( short NumberDevice, short NumberChannel );
    void setMotorReverce( short Number, bool value );

    short getSensorYaw( short Number );//получить данные с сенсора рысканья
    short getSensorPitch( short Number );
    short getSensorRoll( short Number );//получить данные с сенсора вращения/крена
    short getSensorUCH0( short Number );
    short getSensorUCH1( short Number );
    short getSensorUCH2( short Number );
    short getSensorUCH3( short Number );
    short getSensorTX( short Number );
    short getSensorTY( short Number );
    short getSensorFZ( short Number );
    short getSensorValue( short Number, int Param );

    short getMotorCurrent( short Number );//получить ток мотора
    short getMotorVoltage( short Number );//получить напряжение мотора
    short getMotorAngle( short Number );//получить текущую позицию мотора
    short getMotorPGate( short Number );//получить KP
    short getMotorIGate( short Number );//получить KI
    short getMotorState( short Number );//получить статус мотора
    short getMotorMinAngle( short Number );//получить минимальную позицию мотора
    short getMotorMaxAngle( short Number );//получить максималную позицию мотора

    float getPowerVoltage6_1();
    float getPowerVoltage6_2();
    float getPowerVoltage8_1();
    float getPowerVoltage8_2();
    float getPowerVoltage48();
    float getPowerVoltage12();

    float getPowerCurrent6_1();
    float getPowerCurrent6_2();
    float getPowerCurrent8_1();
    float getPowerCurrent8_2();
    float getPowerCurrent48();
    float getPowerCurrent12();

    const char *getRAW();
    std::mutex *getLocker();
};

