#include "MBRead.h"


MBRead::MBRead(void)
{
    mLock = false;
}


MBRead::~MBRead(void)
{
}

//инициализируем (читаем)
void MBRead::Init(const char BUFF_other[])
{
    for(int i=0;i<1472;i++)
	{
		mRXBuffer[i]=BUFF_other[i];
    }
}

//получение данных с сенсоров
#pragma region Sensor

//получить данные с сенсора рысканья
short MBRead::Get_SENSOR_YAW(short NOMB)
{
    return (mRXBuffer[NOMB*16+3] << 8) + (unsigned char)mRXBuffer[NOMB*16+2];

}

short MBRead::Get_SENSOR_PITCH(short NOMB)
{
    return (mRXBuffer[NOMB*16+5] << 8) + (unsigned char)mRXBuffer[NOMB*16+4];

}

//получить данные с сенсора вращения/крена
short MBRead::Get_SENSOR_ROLL(short NOMB)
{
    return (mRXBuffer[NOMB*16+7] << 8) + (unsigned char)mRXBuffer[NOMB*16+6];

}

short MBRead::Get_SENSOR_UCH0(short NOMB)
{
    return (mRXBuffer[NOMB*16+9] << 8) + (unsigned char)mRXBuffer[NOMB*16+8];

}

short MBRead::Get_SENSOR_UCH1(short NOMB)
{
    return (mRXBuffer[NOMB*16+11] << 8) + (unsigned char)mRXBuffer[NOMB*16+10];

}

short MBRead::Get_SENSOR_UCH2(short NOMB)
{
    return (mRXBuffer[NOMB*16+13] << 8) + (unsigned char)mRXBuffer[NOMB*16+12];

}

short MBRead::Get_SENSOR_UCH3(short NOMB)
{
    return (mRXBuffer[NOMB*16+15] << 8) + (unsigned char)mRXBuffer[NOMB*16+14];

}

short MBRead::Get_SENSOR_TX(short NOMB)
{
    return (mRXBuffer[NOMB*16+3] << 8) + (unsigned char)mRXBuffer[NOMB*16+2];

}

short MBRead::Get_SENSOR_TY(short NOMB)
{
    return (mRXBuffer[NOMB*16+5] << 8) + (unsigned char)mRXBuffer[NOMB*16+4];

}

short MBRead::Get_SENSOR_FZ(short NOMB)
{

    return (mRXBuffer[NOMB*16+7] << 8) + (unsigned char)mRXBuffer[NOMB*16+6];

}

#pragma endregion Sensor

//получение данных с моторов
#pragma region Motor

//получить напряжение питания мотора
short MBRead::Get_MOTOR_UBATT(short NOMB)
{
    return (mRXBuffer[NOMB*16+5] << 8) + (unsigned char)mRXBuffer[NOMB*16+4];

}

//получить ток, потребляемый мотором
short MBRead::Get_MOTOR_IMOT(short NOMB)
{
    return (mRXBuffer[NOMB*16+7] << 8) + (unsigned char)mRXBuffer[NOMB*16+6];

}

//получить текщую позицию мотора
short MBRead::Get_MOTOR_CPOS(short NOMB)
{

    if(mReverceMap.at(NOMB))
        return -1*(((unsigned char)mRXBuffer[NOMB*16+3] << 8) + (unsigned char)mRXBuffer[NOMB*16+2]);
    else
        return ((unsigned char)mRXBuffer[NOMB*16+3] << 8) + (unsigned char)mRXBuffer[NOMB*16+2];


}

//получить KP
short MBRead::Get_MOTOR_STIFF(short NOMB)
{
    return (mRXBuffer[NOMB*16+9] << 8) + (unsigned char)mRXBuffer[NOMB*16+8];

}

//получить KI
short MBRead::Get_MOTOR_DAMP(short NOMB)
{
    return (mRXBuffer[NOMB*16+11] << 8) + (unsigned char)mRXBuffer[NOMB*16+10];

}

//получить статус мотора
short MBRead::Get_MOTOR_STAT(short NOMB)
{
    return (unsigned char)mRXBuffer[NOMB*16+1];

}

//получить минимальную позицию мотора
short MBRead::Get_MOTOR_MIN_POS(short NOMB)
{


    if(mReverceMap.at(NOMB))
        return -1*((mRXBuffer[NOMB*16+15] << 8) + (unsigned char)mRXBuffer[NOMB*16+14]);
    else
        return (mRXBuffer[NOMB*16+13] << 8) + (unsigned char)mRXBuffer[NOMB*16+12];

}

//получить максимальную позицию мотора
short MBRead::Get_MOTOR_MAX_POS(short NOMB)
{
    if(mReverceMap.at(NOMB))
        return -1*((mRXBuffer[NOMB*16+13] << 8) + (unsigned char)mRXBuffer[NOMB*16+12]);
    else
        return (mRXBuffer[NOMB*16+15] << 8) + (unsigned char)mRXBuffer[NOMB*16+14];

}

//получить напряжение мотора
float MBRead::Get_MOTOR_U(short NOMB)
{
    return (float)((mRXBuffer[NOMB*2+1409] << 8) + (unsigned char)mRXBuffer[NOMB*2+1408]);

}

//получить ток мотора
float MBRead::Get_MOTOR_I(short NOMB)
{

    return float((mRXBuffer[NOMB*2+12+1409] << 8) + (unsigned char)mRXBuffer[NOMB*2+12+1408]);

}

//получение данных о напряжении источников питания
float MBRead::GetU61()
{

    return (float)((mRXBuffer[0 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[0 * 2 + 1408])/1000;

}

float MBRead::GetU62()
{

    return (float)((mRXBuffer[1 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[1 * 2 + 1408])/1000;

}

float MBRead::GetU81()
{
    return (float)((mRXBuffer[2 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[2 * 2 + 1408])/1000;

}

float MBRead::GetU82()
{
    return (float)((mRXBuffer[3 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[3 * 2 + 1408])/1000;

}

float MBRead::GetU12()
{
    return (float)((mRXBuffer[4 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[1 * 2 + 1408])/1000;

}

float MBRead::GetU48()
{
    return (float)((mRXBuffer[5 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[1 * 2 + 1408])/100;

}

//получение данных о токах источников питания
float MBRead::GetI61()
{
    return (float)((mRXBuffer[0 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[0 * 2 + 12 + 1408])/1000;

}

float MBRead::GetI62()
{
    return (float)((mRXBuffer[1 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[1 * 2 + 12 + 1408])/1000;

}

float MBRead::GetI81()
{
    return (float)((mRXBuffer[2 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[2 * 2 + 12 + 1408])/1000;

}

float MBRead::GetI82()
{
    return (float)((mRXBuffer[3 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[3 * 2 + 12 + 1408])/1000;

}

float MBRead::GetI48()
{
    return (float)((mRXBuffer[5 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[5 * 2 + 12 + 1408])/100;

}

float MBRead::GetI12()
{
    return (float)((mRXBuffer[4 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[4 * 2 + 12 + 1408])/1000;

}

std::map<int, bool> *MBRead::GetReverceMap()
{
    return &mReverceMap;
}

void MBRead::SetReverceMap(std::map<int, bool> *ReverceMap)
{
    mReverceMap=*ReverceMap;
}

void MBRead::SetMinPosMap(std::map<int, int> *MinPosMap)
{
    mMinPosMap=*MinPosMap;
}

void MBRead::SetMaxPosMap(std::map<int, int> *MaxPosMap)
{
    mMaxPosMap=*MaxPosMap;
}

const char *MBRead::GetBuffer()
{
    return mRXBuffer;
}

bool *MBRead::GetLock()
{
    return &mLock;
}

#pragma endregion Motor
