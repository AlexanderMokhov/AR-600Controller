#include "MBRead.h"


MBRead::MBRead(void)
{

}


MBRead::~MBRead(void)
{

}

//инициализируем (читаем)
void MBRead::Init(const char BUFF_other[])
{
    mLocker.lock();
    for(int i=0;i<1472;i++)
	{
		mRXBuffer[i]=BUFF_other[i];
    }
    mLocker.unlock();
}

//получить данные с сенсора рысканья
short MBRead::Get_SENSOR_YAW(short NOMB)
{
    mLocker.lock();
    short sensor_yaw =(mRXBuffer[NOMB*16+3] << 8) + (unsigned char)mRXBuffer[NOMB*16+2];
    mLocker.unlock();
    return sensor_yaw;
}

short MBRead::Get_SENSOR_PITCH(short NOMB)
{
    mLocker.lock();
    short sensor_pitch = (mRXBuffer[NOMB*16+5] << 8) + (unsigned char)mRXBuffer[NOMB*16+4];
    mLocker.unlock();
    return sensor_pitch;
}

//получить данные с сенсора вращения/крена
short MBRead::Get_SENSOR_ROLL(short NOMB)
{
    mLocker.lock();
    short sensor_roll=(mRXBuffer[NOMB*16+7] << 8) + (unsigned char)mRXBuffer[NOMB*16+6];
    mLocker.unlock();
    return sensor_roll;
}

short MBRead::Get_SENSOR_UCH0(short NOMB)
{
    mLocker.lock();
    short sensor_uch0=(mRXBuffer[NOMB*16+9] << 8) + (unsigned char)mRXBuffer[NOMB*16+8];
    mLocker.unlock();
    return sensor_uch0;
}

short MBRead::Get_SENSOR_UCH1(short NOMB)
{
    mLocker.lock();
    short sensor_uch1=(mRXBuffer[NOMB*16+11] << 8) + (unsigned char)mRXBuffer[NOMB*16+10];
    mLocker.unlock();
    return sensor_uch1;
}

short MBRead::Get_SENSOR_UCH2(short NOMB)
{
    mLocker.lock();
    short sensor_uch2=(mRXBuffer[NOMB*16+13] << 8) + (unsigned char)mRXBuffer[NOMB*16+12];
    mLocker.unlock();
    return sensor_uch2;
}

short MBRead::Get_SENSOR_UCH3(short NOMB)
{
    mLocker.lock();
    short sensor_uch3=(mRXBuffer[NOMB*16+15] << 8) + (unsigned char)mRXBuffer[NOMB*16+14];
    mLocker.unlock();
    return sensor_uch3;
}

short MBRead::Get_SENSOR_TX(short NOMB)
{
    mLocker.lock();
    short sensor_tx=(mRXBuffer[NOMB*16+3] << 8) + (unsigned char)mRXBuffer[NOMB*16+2];
    mLocker.unlock();
    return sensor_tx;
}

short MBRead::Get_SENSOR_TY(short NOMB)
{
    mLocker.lock();
    short sensor_ty=(mRXBuffer[NOMB*16+5] << 8) + (unsigned char)mRXBuffer[NOMB*16+4];
    mLocker.unlock();
    return sensor_ty;
}

short MBRead::Get_SENSOR_FZ(short NOMB)
{
    mLocker.lock();
    short sensor_fz=(mRXBuffer[NOMB*16+7] << 8) + (unsigned char)mRXBuffer[NOMB*16+6];
    mLocker.unlock();
    return sensor_fz;
}

//получить напряжение питания мотора
short MBRead::Get_MOTOR_UBATT(short NOMB)
{
    mLocker.lock();
    short motor_ubatt=(mRXBuffer[NOMB*16+5] << 8) + (unsigned char)mRXBuffer[NOMB*16+4];
    mLocker.unlock();
    return motor_ubatt;
}

//получить ток, потребляемый мотором
short MBRead::Get_MOTOR_IMOT(short NOMB)
{
    mLocker.lock();
    short motor_imot=(mRXBuffer[NOMB*16+7] << 8) + (unsigned char)mRXBuffer[NOMB*16+6];
    mLocker.unlock();
    return motor_imot;
}

//получить текщую позицию мотора
short MBRead::Get_MOTOR_CPOS(short NOMB)
{
    short cpos;
    mLocker.lock();
    if(mReverceMap.at(NOMB))
    {
        cpos = -1*(((unsigned char)mRXBuffer[NOMB*16+3] << 8) + (unsigned char)mRXBuffer[NOMB*16+2]);
    }
    else
    {
        cpos = ((unsigned char)mRXBuffer[NOMB*16+3] << 8) + (unsigned char)mRXBuffer[NOMB*16+2];
    }
    mLocker.unlock();
    return cpos;
}

//получить KP
short MBRead::Get_MOTOR_STIFF(short NOMB)
{
    mLocker.lock();
    short motor_stiff=(mRXBuffer[NOMB*16+9] << 8) + (unsigned char)mRXBuffer[NOMB*16+8];
    mLocker.unlock();
    return motor_stiff;
}

//получить KI
short MBRead::Get_MOTOR_DAMP(short NOMB)
{
    mLocker.lock();
    short motor_damp=(mRXBuffer[NOMB*16+11] << 8) + (unsigned char)mRXBuffer[NOMB*16+10];
    mLocker.unlock();
    return motor_damp;
}

short MBRead::Get_MOTOR_TORQUE(short NOMB)
{
    mLocker.lock();
    short motor_torque=(mRXBuffer[NOMB*16+5] << 8) + (unsigned char)mRXBuffer[NOMB*16+4];
    mLocker.unlock();
    return motor_torque;
}

//получить статус мотора
short MBRead::Get_MOTOR_STAT(short NOMB)
{
    mLocker.lock();
    short motor_stat=(unsigned char)mRXBuffer[NOMB*16+1];
    mLocker.unlock();
    return motor_stat;

}

//получить минимальную позицию мотора
short MBRead::Get_MOTOR_MIN_POS(short NOMB)
{
    short minpos;
    mLocker.lock();
    if(mReverceMap.at(NOMB))
    {
        minpos = -1*((mRXBuffer[NOMB*16+15] << 8) + (unsigned char)mRXBuffer[NOMB*16+14]);
    }
    else
    {
        minpos = (mRXBuffer[NOMB*16+13] << 8) + (unsigned char)mRXBuffer[NOMB*16+12];
    }
    mLocker.unlock();
    return minpos;
}

//получить максимальную позицию мотора
short MBRead::Get_MOTOR_MAX_POS(short NOMB)
{
    short maxpos;
    mLocker.lock();
    if(mReverceMap.at(NOMB))
    {
        maxpos = -1*((mRXBuffer[NOMB*16+13] << 8) + (unsigned char)mRXBuffer[NOMB*16+12]);
    }
    else
    {
        maxpos = (mRXBuffer[NOMB*16+15] << 8) + (unsigned char)mRXBuffer[NOMB*16+14];
    }
    mLocker.unlock();
    return maxpos;
}

//получить напряжение мотора
float MBRead::Get_MOTOR_U(short NOMB)
{
    mLocker.lock();
    float motor_u=(float)((mRXBuffer[NOMB*2+1409] << 8) + (unsigned char)mRXBuffer[NOMB*2+1408]);
    mLocker.unlock();
    return motor_u;

}

//получить ток мотора
float MBRead::Get_MOTOR_I(short NOMB)
{
    mLocker.lock();
    float motor_i=(float)((mRXBuffer[NOMB*2+12+1409] << 8) + (unsigned char)mRXBuffer[NOMB*2+12+1408]);
    mLocker.unlock();
    return motor_i;

}

//получение данных о напряжении источников питания
float MBRead::GetU61()
{
    mLocker.lock();
    float u61=(float)((mRXBuffer[0 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[0 * 2 + 1408])/1000;
    mLocker.unlock();
    return u61;

}

float MBRead::GetU62()
{
    mLocker.lock();
    float u62=(float)((mRXBuffer[1 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[1 * 2 + 1408])/1000;
    mLocker.unlock();
    return u62;

}

float MBRead::GetU81()
{
    mLocker.lock();
    float u81=(float)((mRXBuffer[2 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[2 * 2 + 1408])/1000;
    mLocker.unlock();
    return u81;

}

float MBRead::GetU82()
{
    mLocker.lock();
    float u82=(float)((mRXBuffer[3 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[3 * 2 + 1408])/1000;
    mLocker.unlock();
    return u82;

}

float MBRead::GetU12()
{
    mLocker.lock();
    float u12=(float)((mRXBuffer[4 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[1 * 2 + 1408])/1000;
    mLocker.unlock();
    return u12;

}

float MBRead::GetU48()
{
    mLocker.lock();
    float u48=(float)((mRXBuffer[5 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[1 * 2 + 1408])/100;
    mLocker.unlock();
    return u48;

}

//получение данных о токах источников питания
float MBRead::GetI61()
{
    mLocker.lock();
    float i61=(float)((mRXBuffer[0 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[0 * 2 + 12 + 1408])/1000;
    mLocker.unlock();
    return i61;

}

float MBRead::GetI62()
{
    mLocker.lock();
    float i62=(float)((mRXBuffer[1 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[1 * 2 + 12 + 1408])/1000;
    mLocker.unlock();
    return i62;
}

float MBRead::GetI81()
{
    mLocker.lock();
    float i81=(float)((mRXBuffer[2 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[2 * 2 + 12 + 1408])/1000;
    mLocker.unlock();
    return i81;

}

float MBRead::GetI82()
{
    mLocker.lock();
    float i82=(float)((mRXBuffer[3 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[3 * 2 + 12 + 1408])/1000;
    mLocker.unlock();
    return i82;

}

float MBRead::GetI48()
{
    mLocker.lock();
    float i48=(float)((mRXBuffer[5 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[5 * 2 + 12 + 1408])/100;
    mLocker.unlock();
    return i48;

}

float MBRead::GetI12()
{
    mLocker.lock();
    float i12=(float)((mRXBuffer[4 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[4 * 2 + 12 + 1408])/1000;
    mLocker.unlock();
    return i12;

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

std::mutex *MBRead::GetLocker()
{
    return &mLocker;
}
