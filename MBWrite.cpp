#include "MBWrite.h"

#include <stdio.h>
#include <QDebug>


MBWrite::MBWrite(void)
{
}


MBWrite::~MBWrite(void)
{
}

//инициализируем (читаем)
void MBWrite::Init(unsigned char BUFF_other[])
{
    for(int i=0;i<1470;i++)
	{
		mWRBuffer[i]=BUFF_other[i];
	}
}

//инициализируем (установка 12 В)
void MBWrite::Init(void)
{
    for(int i=0;i<1470;i++)
	{
		mWRBuffer[i]=0;
	}
    ON12();
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

//устанвока питания
#pragma region Power

//включить 6 В (1)
void MBWrite::ON61(void)
{
	mWRBuffer[1409] |= 1;
}

//включить 6 В (2)
void MBWrite::ON62(void)
{
	mWRBuffer[1409] |= 2;
}

//включить 8 В (1)
void MBWrite::ON81(void)
{
	mWRBuffer[1409] |= 4;
}

//включить 8 В (2)
void MBWrite::ON82(void)
{
	mWRBuffer[1409] |= 8;
}

//включить 12 В
void MBWrite::ON12(void)
{
    mWRBuffer[1409] |= 16;
}

//включить 48 В
void MBWrite::ON48(void)
{
	mWRBuffer[1409] |= 32;
}

//выключить 6 В (1)
void MBWrite::OFF61(void)
{
	mWRBuffer[1409] &= (255-1);
}

//выключить 6 В (2)
void MBWrite::OFF62(void)
{
	mWRBuffer[1409] &= (255-2);
}

//выключить 8 В (1)
void MBWrite::OFF81(void)
{
	mWRBuffer[1409] &= (255-4);
}

//выключить 8 В (2)
void MBWrite::OFF82(void)
{
	mWRBuffer[1409] &= (255-8);
}

//выключить 12 В
void MBWrite::OFF12(void)
{
	mWRBuffer[1409] &= (255-16);
}

//выключить 48 В
void MBWrite::OFF48(void)
{
	mWRBuffer[1409] &= (255-32);
}

//включить беззвучный режим
void MBWrite::MUTE_ON(void)
{
	mWRBuffer[1409] |= 128;
}

//выключить беззвучный режим
void MBWrite::MUTE_OFF(void)
{
    mWRBuffer[1409] &= (255-128);
}

void MBWrite::AddressUpdate(short NOMB, short NumberMotor)
{
    mWRBuffer[NOMB * 16] = NumberMotor;
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

#pragma endregion Power

//установка значений сенсоров
#pragma region Sensor

void MBWrite::Set_SENSOR_UCH0(short NOMB, short value)
{
	mWRBuffer[NOMB * 16 + 8] = (value>>8);
    mWRBuffer[NOMB * 16 + 9] = value;
}

void MBWrite::Set_SENSOR_UCH1(short NOMB, short value)
{
	mWRBuffer[NOMB * 16 + 10] = (value>>8);
    mWRBuffer[NOMB * 16 + 11] = value;
}

void MBWrite::Set_SENSOR_UCH2(short NOMB, short value)
{
	mWRBuffer[NOMB * 16 + 12] = (value>>8);
    mWRBuffer[NOMB * 16 + 13] = value;
}

void MBWrite::Set_SENSOR_UCH3(short NOMB, short value)
{
	mWRBuffer[NOMB * 16 + 14] = (value>>8);
    mWRBuffer[NOMB * 16 + 15] = value;
}

void MBWrite::SENSOR_OFFSET(short NOMB, unsigned char RXBuffer[])
{
    mWRBuffer[NOMB * 16 + 8] = RXBuffer[NOMB * 16 + 8];
    mWRBuffer[NOMB * 16 + 9] = RXBuffer[NOMB * 16 + 9];

    mWRBuffer[NOMB * 16 + 10] = RXBuffer[NOMB * 16 + 10];
    mWRBuffer[NOMB * 16 + 11] = RXBuffer[NOMB * 16 + 11];

    mWRBuffer[NOMB * 16 + 12] = RXBuffer[NOMB * 16 + 12];
    mWRBuffer[NOMB * 16 + 13] = RXBuffer[NOMB * 16 + 13];

    mWRBuffer[NOMB * 16 + 14] = RXBuffer[NOMB * 16 + 14];
    mWRBuffer[NOMB * 16 + 15] = RXBuffer[NOMB * 16 + 15];
}

void MBWrite::SENSOR_XY_OFFSET(short NOMB, unsigned char RXBuffer[])
{
    mWRBuffer[NOMB * 16 + 2] = RXBuffer[NOMB * 16 + 2];
    mWRBuffer[NOMB * 16 + 3] = RXBuffer[NOMB * 16 + 3];

    mWRBuffer[NOMB * 16 + 4] = RXBuffer[NOMB * 16 + 4];
    mWRBuffer[NOMB * 16 + 5] = RXBuffer[NOMB * 16 + 5];
}

void MBWrite::SENSOR_Z_OFFSET(short NOMB, unsigned char RXBuffer[])
{
    mWRBuffer[NOMB * 16 + 6] = RXBuffer[NOMB * 16 + 6];
    mWRBuffer[NOMB * 16 + 7] = RXBuffer[NOMB * 16 + 7];
}
#pragma endregion Sensor

//установка значений моторов
#pragma region Motor

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
    mWRBuffer[NOMB * 16 + 3] = (value>>8);
    mWRBuffer[NOMB * 16 + 2] = value;
}

void MBWrite::Set_MOTOR_ILIM(short NOMB, short value)
{
	mWRBuffer[NOMB * 16 + 7] = (value>>8);
    mWRBuffer[NOMB * 16 + 6] = value;
}

void MBWrite::Set_MOTOR_STIFF(short NOMB, short value)
{
	mWRBuffer[NOMB * 16 + 9] = (value>>8);
    mWRBuffer[NOMB * 16 + 8] = value;
}

void MBWrite::Set_MOTOR_DAMP(short NOMB, short value)
{
	mWRBuffer[NOMB * 16 + 11] = (value>>8);
    mWRBuffer[NOMB * 16 + 10] = value;
}

void MBWrite::Set_MOTOR_MIN_POS(short NOMB, short value)
{
    mMinPosMap.at(NOMB) = value;//запоминаем отображаемое значение
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
}

void MBWrite::Set_MOTOR_MAX_POS(short NOMB, short value)
{
    mMaxPosMap.at(NOMB) = value;//запоминаем отображаемое значение
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
}

//установить мотор в центральное положение
void MBWrite::MOTOR_CENTER(short NOMB, unsigned char RXBUFF[])
{
	mWRBuffer[NOMB * 16 + 7] = RXBUFF[NOMB * 16 + 3];
    mWRBuffer[NOMB * 16 + 6] = RXBUFF[NOMB * 16 + 2];
}

//остановить мотор
void MBWrite::MOTOR_STOP(short NOMB)
{
	mWRBuffer[NOMB * 16 + 1] &= (255 - 3);
    mWRBuffer[NOMB * 16 + 1] |= 1;
}

//зафиксировать мотор
void MBWrite::MOTOR_TRACE(short NOMB)
{
	mWRBuffer[NOMB * 16 + 1] |= 3;
}

//ослабить мотор
void MBWrite::MOTOR_RELAX(short NOMB)
{
	mWRBuffer[NOMB * 16 + 1] &= (255 - 3);
    mWRBuffer[NOMB * 16 + 1] |= 2;
}

//отменить остановку мотора
void MBWrite::MOTOR_STOP_BR(short NOMB)
{
	mWRBuffer[NOMB * 16 + 1] &= (255 - 3);
}

//установить обратное направление движения мотора
void MBWrite::MOTOR_SET_REVERS(short NOMB)
{
	mWRBuffer[NOMB * 16 + 1] |= 128;
}

//сбросить обртаное направление движения мотора
void MBWrite::MOTOR_CLR_REVERS(short NOMB)
{
	mWRBuffer[NOMB * 16 + 1] &= (255 - 128);
}

#pragma endregion Motor
