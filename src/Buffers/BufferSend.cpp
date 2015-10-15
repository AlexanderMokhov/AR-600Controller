#include "BufferSend.h"

#include <stdio.h>
#include <QDebug>


BufferSend::BufferSend(void)
{
    for(int i=0;i<1472;i++)
    {
        mRAW[i]=0;
    }
    PowerOn12();
}


BufferSend::~BufferSend(void)
{

}

//инициализируем (читаем)
void BufferSend::Init(unsigned char RAW_other[])
{
    mLocker.lock();
    for(int i=0;i<1472;i++)
	{
        mRAW[i]=RAW_other[i];
	}
    mLocker.unlock();
}

//инициализируем (установка 12 В)
void BufferSend::Init(void)
{
    mLocker.lock();
    for(int i=0;i<1472;i++)
	{
        mRAW[i]=0;
	}
    PowerOn12();
    mLocker.unlock();
}

const char *BufferSend::GetRAW()
{
    return mRAW;
}

//установка питания

//включить 6 В (1)
void BufferSend::PowerOn61(void)
{
    mLocker.lock();
    mRAW[1409] |= 1;
    mLocker.unlock();
}

//включить 6 В (2)
void BufferSend::PowerOn62(void)
{
    mLocker.lock();
    mRAW[1409] |= 2;
    mLocker.unlock();
}

//включить 8 В (1)
void BufferSend::PowerOn81(void)
{
    mLocker.lock();
    mRAW[1409] |= 4;
    mLocker.unlock();
}

//включить 8 В (2)
void BufferSend::PowerOn82(void)
{
    mLocker.lock();
    mRAW[1409] |= 8;
    mLocker.unlock();
}

//включить 12 В
void BufferSend::PowerOn12(void)
{
    mLocker.lock();
    mRAW[1409] |= 16;
    mLocker.unlock();
}

//включить 48 В
void BufferSend::PowerOn48(void)
{
    mLocker.lock();
    mRAW[1409] |= 32;
    mLocker.unlock();
}

//выключить 6 В (1)
void BufferSend::PowerOff61(void)
{
    mLocker.lock();
    mRAW[1409] &= (255-1);
    mLocker.unlock();
}

//выключить 6 В (2)
void BufferSend::PowerOff62(void)
{
    mLocker.lock();
    mRAW[1409] &= (255-2);
    mLocker.unlock();
}

//выключить 8 В (1)
void BufferSend::PowerOff81(void)
{
    mLocker.lock();
    mRAW[1409] &= (255-4);
    mLocker.unlock();
}

//выключить 8 В (2)
void BufferSend::PowerOff82(void)
{
    mLocker.lock();
    mRAW[1409] &= (255-8);
    mLocker.unlock();
}

//выключить 12 В
void BufferSend::PowerOff12(void)
{
    mLocker.lock();
    mRAW[1409] &= (255-16);
    mLocker.unlock();
}

//выключить 48 В
void BufferSend::PowerOff48(void)
{
    mLocker.lock();
    mRAW[1409] &= (255-32);
    mLocker.unlock();
}

//включить беззвучный режим
void BufferSend::MuteOn(void)
{
    mLocker.lock();
    mRAW[1409] |= 128;
    mLocker.unlock();
}

//выключить беззвучный режим
void BufferSend::MuteOff(void)
{
    mLocker.lock();
    mRAW[1409] &= (255-128);
    mLocker.unlock();
}

void BufferSend::SetDeviceChannel(short NumberDevice, short NumberChannel)
{
    mMotorData[NumberDevice].Channel = NumberChannel;
    mLocker.lock();
    mRAW[NumberChannel * 16] = NumberDevice;
    mLocker.unlock();
}

std::mutex *BufferSend::GetLocker()
{
    return &mLocker;
}

//установка значений сенсоров

void BufferSend::SetSensorUCH0(short Number, short value)
{
    mLocker.lock();
    mRAW[mMotorData[Number].Channel * 16 + 8] = (value>>8);
    mRAW[mMotorData[Number].Channel * 16 + 9] = value;
    mLocker.unlock();
}

void BufferSend::SetSensorUCH1(short Number, short value)
{
    mLocker.lock();
    mRAW[mMotorData[Number].Channel * 16 + 10] = (value>>8);
    mRAW[mMotorData[Number].Channel * 16 + 11] = value;
    mLocker.unlock();
}

void BufferSend::SetSensorUCH2(short Number, short value)
{
    mLocker.lock();
    mRAW[mMotorData[Number].Channel * 16 + 12] = (value>>8);
    mRAW[mMotorData[Number].Channel * 16 + 13] = value;
    mLocker.unlock();
}

void BufferSend::SetSensorUCH3(short Number, short value)
{
    mLocker.lock();
    mRAW[mMotorData[Number].Channel * 16 + 14] = (value>>8);
    mRAW[mMotorData[Number].Channel * 16 + 15] = value;
    mLocker.unlock();
}
//установка значений моторов

//повернуть мотор на угол
void BufferSend::SetMotorAngle(short Number, short value)
{
    short MinPos = mMotorData[Number].MinAngle;
    short MaxPos = mMotorData[Number].MaxAngle;
    if(value < MinPos)
    {
        qDebug() << QString::number(Number) << " !!!Значение" << QString::number(value)
                 << "ниже минимума" << QString::number(MinPos) << endl;
        value = MinPos;

    }
    else if(value > MaxPos)
    {
        qDebug() << QString::number(Number) << " !!!Значение" << QString::number(value)
                 << "выше максимума" << QString::number(MaxPos) << endl;
        value = MaxPos;

    }
    if(mMotorData[Number].isReverce)
    {
        value = -1*value;
    }
    mLocker.lock();
    mRAW[mMotorData[Number].Channel * 16 + 3] = (value>>8);
    mRAW[mMotorData[Number].Channel * 16 + 2] = value;
    mLocker.unlock();
}

void BufferSend::SetMotorCalibration(short Number, short value)
{
    mLocker.lock();
    mRAW[mMotorData[Number].Channel * 16 + 7] = (value>>8);
    mRAW[mMotorData[Number].Channel * 16 + 6] = value;
    mLocker.unlock();
}

void BufferSend::SetMotorStiff(short Number, short value)
{
    mLocker.lock();
    mRAW[mMotorData[Number].Channel * 16 + 9] = (value>>8);
    mRAW[mMotorData[Number].Channel * 16 + 8] = value;
    mLocker.unlock();
}

void BufferSend::SetMotorDump(short Number, short value)
{
    mLocker.lock();
    mRAW[mMotorData[Number].Channel * 16 + 11] = (value>>8);
    mRAW[mMotorData[Number].Channel * 16 + 10] = value;
    mLocker.unlock();
}

void BufferSend::SetMotorTorque(short Number, short value)
{
    mLocker.lock();
    mRAW[mMotorData[Number].Channel * 16 + 5] = (value>>8);
    mRAW[mMotorData[Number].Channel * 16 + 4] = value;
    mLocker.unlock();
}

void BufferSend::SetMotorMinAngle(short Number, short value)
{
    mMotorData[Number].MinAngle = value;//запоминаем отображаемое значение
    mLocker.lock();
    if(mMotorData[Number].isReverce)
    {
        mRAW[mMotorData[Number].Channel * 16 + 15] = (-1*value>>8);
        mRAW[mMotorData[Number].Channel * 16 + 14] = -1*value;
    }
    else
    {
        mRAW[mMotorData[Number].Channel * 16 + 13] = (value>>8);
        mRAW[mMotorData[Number].Channel * 16 + 12] = value;
    }
    mLocker.unlock();
}

void BufferSend::SetMotorMaxAngle(short Number, short value)
{
    mMotorData[Number].MaxAngle = value;//запоминаем отображаемое значение
    mLocker.lock();
    if(mMotorData[Number].isReverce)
    {
        mRAW[mMotorData[Number].Channel * 16 + 13] = (-1*value>>8);
        mRAW[mMotorData[Number].Channel * 16 + 12] = -1*value;
    }
    else
    {
        mRAW[mMotorData[Number].Channel * 16 + 15] = (value>>8);
        mRAW[mMotorData[Number].Channel * 16 + 14] = value;
    }
    mLocker.unlock();
}

void BufferSend::SetMotorEnable(short Number, bool value)
{
    mMotorData[Number].isEnable = value;
}

void BufferSend::SetMotorReverce(short Number, bool value)
{
    mMotorData[Number].isReverce = value;
}

//остановить мотор
void BufferSend::MotorStop(short Number)
{
    mLocker.lock();
    mRAW[mMotorData[Number].Channel * 16 + 1] &= (255 - 3);
    mRAW[mMotorData[Number].Channel * 16 + 1] |= 1;
    mLocker.unlock();
}

//зафиксировать мотор
void BufferSend::MotorTrace(short Number)
{
    mLocker.lock();
    if(mMotorData[Number].isEnable)
    {
        mRAW[mMotorData[Number].Channel * 16 + 1] |= 3;
    }
    mLocker.unlock();
}

//ослабить мотор
void BufferSend::MotorRelax(short Number)
{
    mLocker.lock();
    mRAW[mMotorData[Number].Channel * 16 + 1] &= (255 - 3);
    mRAW[mMotorData[Number].Channel * 16 + 1] |= 2;
    mLocker.unlock();
}

//отменить остановку мотора
void BufferSend::MotorStopBrake(short Number)
{
    mLocker.lock();
    mRAW[mMotorData[Number].Channel * 16 + 1] &= (255 - 3);
    mLocker.unlock();
}

short BufferSend::GetMotorTorque(short Number)
{
    mLocker.lock();
    short motor_torque=(mRAW[mMotorData[Number].Channel*16+5] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+4];
    mLocker.unlock();
    return motor_torque;
}
