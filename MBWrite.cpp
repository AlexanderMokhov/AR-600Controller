#include "MBWrite.h"

#include <stdio.h>


MBWrite::MBWrite(void)
{
}


MBWrite::~MBWrite(void)
{
}

//инициализируем (читаем)
void MBWrite::init(unsigned char BUFF_other[])
{
    for(int i=0;i<1470;i++)
	{
		WRBUFF[i]=BUFF_other[i];
	}
}

//инициализируем (установка 12 В)
void MBWrite::init(void)
{
    for(int i=0;i<1470;i++)
	{
		WRBUFF[i]=0;
	}
    ON12();
}

void MBWrite::DebugPrint()
{
    printf("DebugPrint");
    for(unsigned int i = 0; i < 1471; i++)
    {
        printf("%d \n", WRBUFF[i]);
    }
}

const char *MBWrite::GetBuffer()
{
    return WRBUFF;
}

//устанвока питания
#pragma region Power

//включить 6 В (1)
void MBWrite::ON61(void)
{
	WRBUFF[1409] |= 1;
}

//включить 6 В (2)
void MBWrite::ON62(void)
{
	WRBUFF[1409] |= 2;
}

//включить 8 В (1)
void MBWrite::ON81(void)
{
	WRBUFF[1409] |= 4;
}

//включить 8 В (2)
void MBWrite::ON82(void)
{
	WRBUFF[1409] |= 8;
}

//включить 12 В
void MBWrite::ON12(void)
{
    WRBUFF[1409] |= 16;
}

//включить 48 В
void MBWrite::ON48(void)
{
	WRBUFF[1409] |= 32;
}

//выключить 6 В (1)
void MBWrite::OFF61(void)
{
	WRBUFF[1409] &= (255-1);
}

//выключить 6 В (2)
void MBWrite::OFF62(void)
{
	WRBUFF[1409] &= (255-2);
}

//выключить 8 В (1)
void MBWrite::OFF81(void)
{
	WRBUFF[1409] &= (255-4);
}

//выключить 8 В (2)
void MBWrite::OFF82(void)
{
	WRBUFF[1409] &= (255-8);
}

//выключить 12 В
void MBWrite::OFF12(void)
{
	WRBUFF[1409] &= (255-16);
}

//выключить 48 В
void MBWrite::OFF48(void)
{
	WRBUFF[1409] &= (255-32);
}

//включить беззвучный режим
void MBWrite::MUTE_ON(void)
{
	WRBUFF[1409] |= 128;
}

//выключить беззвучный режим
void MBWrite::MUTE_OFF(void)
{
    WRBUFF[1409] &= (255-128);
}

void MBWrite::AddressUpdate(short number, short buffAddr)
{
    WRBUFF[number * 16] = buffAddr;
}

#pragma endregion Power

//установка значений сенсоров
#pragma region Sensor

void MBWrite::SENSOR_UCH0_set(short NOMB, short value)
{
	WRBUFF[NOMB * 16 + 8] = (value>>8);
    WRBUFF[NOMB * 16 + 9] = value;
}

void MBWrite::SENSOR_UCH1_set(short NOMB, short value)
{
	WRBUFF[NOMB * 16 + 10] = (value>>8);
    WRBUFF[NOMB * 16 + 11] = value;
}

void MBWrite::SENSOR_UCH2_set(short NOMB, short value)
{
	WRBUFF[NOMB * 16 + 12] = (value>>8);
    WRBUFF[NOMB * 16 + 13] = value;
}

void MBWrite::SENSOR_UCH3_set(short NOMB, short value)
{
	WRBUFF[NOMB * 16 + 14] = (value>>8);
    WRBUFF[NOMB * 16 + 15] = value;
}

void MBWrite::SENSOR_OFFSET(short NOMB, unsigned char RXBUFF[])
{
	WRBUFF[NOMB * 16 + 8] = RXBUFF[NOMB * 16 + 8];
    WRBUFF[NOMB * 16 + 9] = RXBUFF[NOMB * 16 + 9];

    WRBUFF[NOMB * 16 + 10] = RXBUFF[NOMB * 16 + 10];
    WRBUFF[NOMB * 16 + 11] = RXBUFF[NOMB * 16 + 11];

    WRBUFF[NOMB * 16 + 12] = RXBUFF[NOMB * 16 + 12];
    WRBUFF[NOMB * 16 + 13] = RXBUFF[NOMB * 16 + 13];

    WRBUFF[NOMB * 16 + 14] = RXBUFF[NOMB * 16 + 14];
    WRBUFF[NOMB * 16 + 15] = RXBUFF[NOMB * 16 + 15];
}

void MBWrite::SENSOR_XY_OFFSET(short NOMB, unsigned char RXBUFF[])
{
	WRBUFF[NOMB * 16 + 2] = RXBUFF[NOMB * 16 + 2];
    WRBUFF[NOMB * 16 + 3] = RXBUFF[NOMB * 16 + 3];

    WRBUFF[NOMB * 16 + 4] = RXBUFF[NOMB * 16 + 4];
    WRBUFF[NOMB * 16 + 5] = RXBUFF[NOMB * 16 + 5];
}

void MBWrite::SENSOR_Z_OFFSET(short NOMB, unsigned char RXBUFF[])
{
	WRBUFF[NOMB * 16 + 6] = RXBUFF[NOMB * 16 + 6];
    WRBUFF[NOMB * 16 + 7] = RXBUFF[NOMB * 16 + 7];
}
#pragma endregion Sensor

//установка значений моторов
#pragma region Motor

//повернуть мотор на угол
void MBWrite::MOTOR_ANGLE_set(short NOMB, short value)
{
	WRBUFF[NOMB * 16 + 3] = (value>>8);
    WRBUFF[NOMB * 16 + 2] = value;
}

void MBWrite::MOTOR_ILIM_set(short NOMB, short value)
{
	WRBUFF[NOMB * 16 + 7] = (value>>8);
    WRBUFF[NOMB * 16 + 6] = value;
}

void MBWrite::MOTOR_STIFF_set(short NOMB, short value)
{
	WRBUFF[NOMB * 16 + 9] = (value>>8);
    WRBUFF[NOMB * 16 + 8] = value;
}

void MBWrite::MOTOR_DAMP_set(short NOMB, short value)
{
	WRBUFF[NOMB * 16 + 11] = (value>>8);
    WRBUFF[NOMB * 16 + 10] = value;
}

void MBWrite::MOTOR_POS_MIN_set(short NOMB, short value)
{
	WRBUFF[NOMB * 16 + 13] = (value>>8);
    WRBUFF[NOMB * 16 + 12] = value;
}

void MBWrite::MOTOR_POS_MAX_set(short NOMB, short value)
{
	WRBUFF[NOMB * 16 + 15] = (value>>8);
    WRBUFF[NOMB * 16 + 14] = value;
}

//установить мотор в центральное положение
void MBWrite::MOTOR_CENTER(short NOMB, unsigned char RXBUFF[])
{
	WRBUFF[NOMB * 16 + 7] = RXBUFF[NOMB * 16 + 3];
    WRBUFF[NOMB * 16 + 6] = RXBUFF[NOMB * 16 + 2];
}

//остановить мотор
void MBWrite::MOTOR_STOP(short NOMB)
{
	WRBUFF[NOMB * 16 + 1] &= (255 - 3);
    WRBUFF[NOMB * 16 + 1] |= 1;
}

//зафиксировать мотор
void MBWrite::MOTOR_TRACE(short NOMB)
{
	WRBUFF[NOMB * 16 + 1] |= 3;
}

//ослабить мотор
void MBWrite::MOTOR_RELAX(short NOMB)
{
	WRBUFF[NOMB * 16 + 1] &= (255 - 3);
    WRBUFF[NOMB * 16 + 1] |= 2;
}

//отменить остановку мотора
void MBWrite::MOTOR_STOP_BR(short NOMB)
{
	WRBUFF[NOMB * 16 + 1] &= (255 - 3);
}

//установить обратное направление движения мотора
void MBWrite::MOTOR_SET_REVERS(short NOMB)
{
	WRBUFF[NOMB * 16 + 1] |= 128;
}

//сбросить обртаное направление движения мотора
void MBWrite::MOTOR_CLR_REVERS(short NOMB)
{
	WRBUFF[NOMB * 16 + 1] &= (255 - 128);
}

#pragma endregion Motor
