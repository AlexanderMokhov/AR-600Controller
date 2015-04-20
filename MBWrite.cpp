#include "MBWrite.h"

#include <stdio.h>
#include <QDebug>


MBWrite::MBWrite(void)
{
    for(int i=0;i<1470;i++)
    {
        mWRBuffer[i]=0;
    }
    //ON12();
}


MBWrite::~MBWrite(void)
{

}

//инициализируем (читаем)
void MBWrite::Init(unsigned char BUFF_other[])
{
    mLocker.lock();
    for(int i=0;i<1470;i++)
	{
		mWRBuffer[i]=BUFF_other[i];
	}
    mLocker.unlock();
}

//инициализируем (установка 12 В)
void MBWrite::Init(void)
{
    mLocker.lock();
    for(int i=0;i<1470;i++)
	{
		mWRBuffer[i]=0;
	}
    ON12();
    mLocker.unlock();
}

void MBWrite::DebugPrint()
{
    printf("DebugPrint");
    for(unsigned int i = 0; i < 1471; i++)
    {
        printf("%d \n", mWRBuffer[i]);
    }
}

const char *MBWrite::GetBuffer()
{
    return mWRBuffer;
}

//устанвка питания

//включить 6 В (1)
void MBWrite::ON61(void)
{
    mLocker.lock();
	mWRBuffer[1409] |= 1;
    mLocker.unlock();
}

//включить 6 В (2)
void MBWrite::ON62(void)
{
    mLocker.lock();
	mWRBuffer[1409] |= 2;
    mLocker.unlock();
}

//включить 8 В (1)
void MBWrite::ON81(void)
{
    mLocker.lock();
	mWRBuffer[1409] |= 4;
    mLocker.unlock();
}

//включить 8 В (2)
void MBWrite::ON82(void)
{
    mLocker.lock();
	mWRBuffer[1409] |= 8;
    mLocker.unlock();
}

//включить 12 В
void MBWrite::ON12(void)
{
    mLocker.lock();
    mWRBuffer[1409] |= 16;
    mLocker.unlock();
}

//включить 48 В
void MBWrite::ON48(void)
{
    mLocker.lock();
	mWRBuffer[1409] |= 32;
    mLocker.unlock();
}

//выключить 6 В (1)
void MBWrite::OFF61(void)
{
    mLocker.lock();
	mWRBuffer[1409] &= (255-1);
    mLocker.unlock();
}

//выключить 6 В (2)
void MBWrite::OFF62(void)
{
    mLocker.lock();
	mWRBuffer[1409] &= (255-2);
    mLocker.unlock();
}

//выключить 8 В (1)
void MBWrite::OFF81(void)
{
    mLocker.lock();
	mWRBuffer[1409] &= (255-4);
    mLocker.unlock();
}

//выключить 8 В (2)
void MBWrite::OFF82(void)
{
    mLocker.lock();
	mWRBuffer[1409] &= (255-8);
    mLocker.unlock();
}

//выключить 12 В
void MBWrite::OFF12(void)
{
    mLocker.lock();
	mWRBuffer[1409] &= (255-16);
    mLocker.unlock();
}

//выключить 48 В
void MBWrite::OFF48(void)
{
    mLocker.lock();
	mWRBuffer[1409] &= (255-32);
    mLocker.unlock();
}

//включить беззвучный режим
void MBWrite::MUTE_ON(void)
{
    mLocker.lock();
	mWRBuffer[1409] |= 128;
    mLocker.unlock();
}

//выключить беззвучный режим
void MBWrite::MUTE_OFF(void)
{
    mLocker.lock();
    mWRBuffer[1409] &= (255-128);
    mLocker.unlock();
}

void MBWrite::AddressUpdate(short NOMB, short NumberMotor)
{
    mLocker.lock();
    mWRBuffer[NOMB * 16] = NumberMotor;
    mLocker.unlock();
}

std::map<int, bool> *MBWrite::GetReverceMap()
{
    return &mReverceMap;
}

std::map<int, int> *MBWrite::GetMinPosMap()
{
    return &mMinPosMap;
}

std::map<int, int> *MBWrite::GetMaxPosMap()
{
    return &mMaxPosMap;
}

std::mutex *MBWrite::GetLocker()
{
    return &mLocker;
}

//установка значений сенсоров

void MBWrite::Set_SENSOR_UCH0(short NOMB, short value)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 8] = (value>>8);
    mWRBuffer[NOMB * 16 + 9] = value;
    mLocker.unlock();
}

void MBWrite::Set_SENSOR_UCH1(short NOMB, short value)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 10] = (value>>8);
    mWRBuffer[NOMB * 16 + 11] = value;
    mLocker.unlock();
}

void MBWrite::Set_SENSOR_UCH2(short NOMB, short value)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 12] = (value>>8);
    mWRBuffer[NOMB * 16 + 13] = value;
    mLocker.unlock();
}

void MBWrite::Set_SENSOR_UCH3(short NOMB, short value)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 14] = (value>>8);
    mWRBuffer[NOMB * 16 + 15] = value;
    mLocker.unlock();
}

void MBWrite::SENSOR_OFFSET(short NOMB,const char RXBuffer[])
{
    mLocker.lock();
    mWRBuffer[NOMB * 16 + 8] = RXBuffer[NOMB * 16 + 8];
    mWRBuffer[NOMB * 16 + 9] = RXBuffer[NOMB * 16 + 9];

    mWRBuffer[NOMB * 16 + 10] = RXBuffer[NOMB * 16 + 10];
    mWRBuffer[NOMB * 16 + 11] = RXBuffer[NOMB * 16 + 11];

    mWRBuffer[NOMB * 16 + 12] = RXBuffer[NOMB * 16 + 12];
    mWRBuffer[NOMB * 16 + 13] = RXBuffer[NOMB * 16 + 13];

    mWRBuffer[NOMB * 16 + 14] = RXBuffer[NOMB * 16 + 14];
    mWRBuffer[NOMB * 16 + 15] = RXBuffer[NOMB * 16 + 15];
    mLocker.unlock();
}

void MBWrite::SENSOR_XY_OFFSET(short NOMB,const char RXBuffer[])
{
    mLocker.lock();
    mWRBuffer[NOMB * 16 + 2] = RXBuffer[NOMB * 16 + 2];
    mWRBuffer[NOMB * 16 + 3] = RXBuffer[NOMB * 16 + 3];

    mWRBuffer[NOMB * 16 + 4] = RXBuffer[NOMB * 16 + 4];
    mWRBuffer[NOMB * 16 + 5] = RXBuffer[NOMB * 16 + 5];
    mLocker.unlock();
}

void MBWrite::SENSOR_Z_OFFSET(short NOMB,const char RXBuffer[])
{
    mLocker.lock();
    mWRBuffer[NOMB * 16 + 6] = RXBuffer[NOMB * 16 + 6];
    mWRBuffer[NOMB * 16 + 7] = RXBuffer[NOMB * 16 + 7];
    mLocker.unlock();
}

//установка значений моторов

//повернуть мотор на угол
void MBWrite::Set_MOTOR_ANGLE(short NOMB, short value)
{
    mMinPos=mMinPosMap.at(NOMB);
    mMaxPos=mMaxPosMap.at(NOMB);
    if(value < mMinPos)
    {
        qDebug() << "!!!Значение" << QString::number(value) << "ниже минимума" << QString::number(mMinPos) << endl;
        value = mMinPos;

    }
    else if(value > mMaxPos)
    {
        qDebug() << "!!!Значение" << QString::number(value) << "выше максимума" << QString::number(mMaxPos) << endl;
        value = mMaxPos;

    }
    if(mReverceMap.at(NOMB))
    {
        value = -1*value;
    }
    mLocker.lock();
    mWRBuffer[NOMB * 16 + 3] = (value>>8);
    mWRBuffer[NOMB * 16 + 2] = value;
    mLocker.unlock();
}

void MBWrite::Set_MOTOR_ILIM(short NOMB, short value)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 7] = (value>>8);
    mWRBuffer[NOMB * 16 + 6] = value;
    mLocker.unlock();
}

void MBWrite::Set_MOTOR_STIFF(short NOMB, short value)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 9] = (value>>8);
    mWRBuffer[NOMB * 16 + 8] = value;
    mLocker.unlock();
}

void MBWrite::Set_MOTOR_DAMP(short NOMB, short value)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 11] = (value>>8);
    mWRBuffer[NOMB * 16 + 10] = value;
    mLocker.unlock();
}

void MBWrite::Set_MOTOR_MIN_POS(short NOMB, short value)
{
    mMinPosMap.at(NOMB) = value;//запоминаем отображаемое значение
    mLocker.lock();
    if(mReverceMap.at(NOMB))
    {
        mWRBuffer[NOMB * 16 + 15] = (-1*value>>8);
        mWRBuffer[NOMB * 16 + 14] = -1*value;
    }
    else
    {
        mWRBuffer[NOMB * 16 + 13] = (value>>8);
        mWRBuffer[NOMB * 16 + 12] = value;
    }
    mLocker.unlock();
}

void MBWrite::Set_MOTOR_MAX_POS(short NOMB, short value)
{
    mMaxPosMap.at(NOMB) = value;//запоминаем отображаемое значение
    mLocker.lock();
    if(mReverceMap.at(NOMB))
    {
        mWRBuffer[NOMB * 16 + 13] = (-1*value>>8);
        mWRBuffer[NOMB * 16 + 12] = -1*value;
    }
    else
    {
        mWRBuffer[NOMB * 16 + 15] = (value>>8);
        mWRBuffer[NOMB * 16 + 14] = value;
    }
    mLocker.unlock();
}

//установить мотор в центральное положение
void MBWrite::MOTOR_CENTER(short NOMB, unsigned char RXBUFF[])
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 7] = RXBUFF[NOMB * 16 + 3];
    mWRBuffer[NOMB * 16 + 6] = RXBUFF[NOMB * 16 + 2];
    mLocker.unlock();
}

//остановить мотор
void MBWrite::MOTOR_STOP(short NOMB)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 1] &= (255 - 3);
    mWRBuffer[NOMB * 16 + 1] |= 1;
    mLocker.unlock();
}

//зафиксировать мотор
void MBWrite::MOTOR_TRACE(short NOMB)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 1] |= 3;
    mLocker.unlock();
}

//ослабить мотор
void MBWrite::MOTOR_RELAX(short NOMB)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 1] &= (255 - 3);
    mWRBuffer[NOMB * 16 + 1] |= 2;
    mLocker.unlock();
}

//отменить остановку мотора
void MBWrite::MOTOR_STOP_BR(short NOMB)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 1] &= (255 - 3);
    mLocker.unlock();
}

//установить обратное направление движения мотора
void MBWrite::MOTOR_SET_REVERS(short NOMB)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 1] |= 128;
    mLocker.unlock();
}

//сбросить обртаное направление движения мотора
void MBWrite::MOTOR_CLR_REVERS(short NOMB)
{
    mLocker.lock();
	mWRBuffer[NOMB * 16 + 1] &= (255 - 128);
    mLocker.unlock();
}
