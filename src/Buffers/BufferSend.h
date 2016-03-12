#pragma once

#include <iostream>
#include <map>
#include <mutex>
#include <stdlib.h>

#include "BufferDefinition.h"

class BufferSend
{
public:
    // public methods
    BufferSend(void);
    ~BufferSend(void);

    //инициализация
    void initialize( unsigned char RAW_other[] );
    void initialize(void);
    const char *getRAW();
    int getSize(){ return bufferSize; }

    //датчик усилия
    void setSensorUCH0( short Number, short value );
    void setSensorUCH1( short Number, short value );
    void setSensorUCH2( short Number, short value );
    void setSensorUCH3( short Number, short value );

    //управление моторами
    void setMotorAngle( short Number, short value );
    void setMotorShiftValue( short Number, short value );
    void setMotorPGate( short Number, short value );//установить KP
    void setMotorIGate( short Number, short value );//установить KI
    void setMotorDGate( short Number, short value );//установить KD
    void setMotorMinAngle( short Number, short value );
    void setMotorMaxAngle( short Number, short value );
    void setMotorEnable( short Number, bool value );
    void setMotorReverceState( short Number, bool value );

    short getMotorDGate( short Number);
    //изменение состояния мотора
    void motorStop( short Number );//динамическое торможение
    void motorTrace( short Number );//режим следование за положением
    void motorRelax( short Number );//убрать фиксацию мотора
    void motorStopBrake( short Number );//режим фиксации

    //управление питанием
    void onPower6_1(void);
    void onPower6_2(void);
    void onPower8_1(void);
    void onPower8_2(void);
    void onPower12(void);
    void onPower48(void);

    void offPower6_1(void);
    void offPower6_2(void);
    void offPower8_1(void);
    void offPower8_2(void);
    void offPower12(void);
    void offPower48(void);

    //управление звуком
    void onMute(void);
    void offMute(void);

    //добавить номер номер устройства в отправляемый буфер
    void setDeviceChannel( short NumberDevice, short NumberChannel );

    std::mutex *getLocker();
private:
    // private variable
    char m_RAW [bufferSize];
    std::mutex m_locker;
    deviceData m_motorsData[channelsNumber];

    // private methods
    void writeInt16(uint16_t address, int16_t value);
};

