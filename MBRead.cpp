#include "MBRead.h"


MBRead::MBRead(void)
{
    mLocker = false;
}


MBRead::~MBRead(void)
{

}

//инициализируем (читаем)
void MBRead::Init(const char BUFF_other[])
{
    while(mLocker){;}
    mLocker=true;
    for(int i=0;i<1472;i++)
	{
		mRXBuffer[i]=BUFF_other[i];
    }
    mLocker=false;
}

//получить данные с сенсора рысканья
short MBRead::Get_SENSOR_YAW(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short sensor_yaw =(mRXBuffer[NOMB*16+3] << 8) + (unsigned char)mRXBuffer[NOMB*16+2];
    mLocker=false;
    return sensor_yaw;

}

short MBRead::Get_SENSOR_PITCH(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short sensor_pitch = (mRXBuffer[NOMB*16+5] << 8) + (unsigned char)mRXBuffer[NOMB*16+4];
    mLocker=false;
    return sensor_pitch;

}

//получить данные с сенсора вращения/крена
short MBRead::Get_SENSOR_ROLL(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short sensor_roll=(mRXBuffer[NOMB*16+7] << 8) + (unsigned char)mRXBuffer[NOMB*16+6];
    mLocker=false;
    return sensor_roll;


}

short MBRead::Get_SENSOR_UCH0(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short sensor_uch0=(mRXBuffer[NOMB*16+9] << 8) + (unsigned char)mRXBuffer[NOMB*16+8];
    mLocker=false;
    return sensor_uch0;


}

short MBRead::Get_SENSOR_UCH1(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short sensor_uch1=(mRXBuffer[NOMB*16+11] << 8) + (unsigned char)mRXBuffer[NOMB*16+10];
    mLocker=false;
    return sensor_uch1;


}

short MBRead::Get_SENSOR_UCH2(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short sensor_uch2=(mRXBuffer[NOMB*16+13] << 8) + (unsigned char)mRXBuffer[NOMB*16+12];
    mLocker=false;
    return sensor_uch2;


}

short MBRead::Get_SENSOR_UCH3(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short sensor_uch3=(mRXBuffer[NOMB*16+15] << 8) + (unsigned char)mRXBuffer[NOMB*16+14];
    mLocker=false;
    return sensor_uch3;


}

short MBRead::Get_SENSOR_TX(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short sensor_tx=(mRXBuffer[NOMB*16+3] << 8) + (unsigned char)mRXBuffer[NOMB*16+2];
    mLocker=false;
    return sensor_tx;


}

short MBRead::Get_SENSOR_TY(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short sensor_ty=(mRXBuffer[NOMB*16+5] << 8) + (unsigned char)mRXBuffer[NOMB*16+4];
    mLocker=false;
    return sensor_ty;


}

short MBRead::Get_SENSOR_FZ(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short sensor_fz=(mRXBuffer[NOMB*16+7] << 8) + (unsigned char)mRXBuffer[NOMB*16+6];
    mLocker=false;
    return sensor_fz;


}

//получить напряжение питания мотора
short MBRead::Get_MOTOR_UBATT(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short motor_ubatt=(mRXBuffer[NOMB*16+5] << 8) + (unsigned char)mRXBuffer[NOMB*16+4];
    mLocker=false;
    return motor_ubatt;


}

//получить ток, потребляемый мотором
short MBRead::Get_MOTOR_IMOT(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short motor_imot=(mRXBuffer[NOMB*16+7] << 8) + (unsigned char)mRXBuffer[NOMB*16+6];
    mLocker=false;
    return motor_imot;


}

//получить текщую позицию мотора
short MBRead::Get_MOTOR_CPOS(short NOMB)
{

    while(mLocker){;}
    mLocker=true;
    if(mReverceMap.at(NOMB))
    {
        short cpos = -1*(((unsigned char)mRXBuffer[NOMB*16+3] << 8) + (unsigned char)mRXBuffer[NOMB*16+2]);
        mLocker=false;
        return cpos;
    }
    else
    {
        short cpos = ((unsigned char)mRXBuffer[NOMB*16+3] << 8) + (unsigned char)mRXBuffer[NOMB*16+2];
        mLocker=false;
        return cpos;
    }


}

//получить KP
short MBRead::Get_MOTOR_STIFF(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short motor_stiff=(mRXBuffer[NOMB*16+9] << 8) + (unsigned char)mRXBuffer[NOMB*16+8];
    mLocker=false;
    return motor_stiff;

}

//получить KI
short MBRead::Get_MOTOR_DAMP(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short motor_damp=(mRXBuffer[NOMB*16+11] << 8) + (unsigned char)mRXBuffer[NOMB*16+10];
    mLocker=false;
    return motor_damp;

}

//получить статус мотора
short MBRead::Get_MOTOR_STAT(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    short motor_stat=(unsigned char)mRXBuffer[NOMB*16+1];
    mLocker=false;
    return motor_stat;

}

//получить минимальную позицию мотора
short MBRead::Get_MOTOR_MIN_POS(short NOMB)
{
    while(mLocker){;}
    mLocker=true;

    if(mReverceMap.at(NOMB))
    {
        short minpos = -1*((mRXBuffer[NOMB*16+15] << 8) + (unsigned char)mRXBuffer[NOMB*16+14]);
        mLocker=false;
        return minpos;
    }
    else
    {
        short minpos = (mRXBuffer[NOMB*16+13] << 8) + (unsigned char)mRXBuffer[NOMB*16+12];
        mLocker=false;
        return minpos;
    }

}

//получить максимальную позицию мотора
short MBRead::Get_MOTOR_MAX_POS(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    if(mReverceMap.at(NOMB))
    {
        short maxpos = -1*((mRXBuffer[NOMB*16+13] << 8) + (unsigned char)mRXBuffer[NOMB*16+12]);
        mLocker=false;
        return maxpos;
    }
    else
    {
        short maxpos = (mRXBuffer[NOMB*16+15] << 8) + (unsigned char)mRXBuffer[NOMB*16+14];
        mLocker=false;
        return maxpos;
    }

}

//получить напряжение мотора
float MBRead::Get_MOTOR_U(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    float motor_u=(float)((mRXBuffer[NOMB*2+1409] << 8) + (unsigned char)mRXBuffer[NOMB*2+1408]);
    mLocker=false;
    return motor_u;

}

//получить ток мотора
float MBRead::Get_MOTOR_I(short NOMB)
{
    while(mLocker){;}
    mLocker=true;
    float motor_i=(float)((mRXBuffer[NOMB*2+12+1409] << 8) + (unsigned char)mRXBuffer[NOMB*2+12+1408]);
    mLocker=false;
    return motor_i;

}

//получение данных о напряжении источников питания
float MBRead::GetU61()
{
    while(mLocker){;}
    mLocker=true;
    float u61=(float)((mRXBuffer[0 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[0 * 2 + 1408])/1000;
    mLocker=false;
    return u61;

}

float MBRead::GetU62()
{
    while(mLocker){;}
    mLocker=true;
    float u62=(float)((mRXBuffer[1 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[1 * 2 + 1408])/1000;
    mLocker=false;
    return u62;

}

float MBRead::GetU81()
{
    while(mLocker){;}
    mLocker=true;
    float u81=(float)((mRXBuffer[2 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[2 * 2 + 1408])/1000;
    mLocker=false;
    return u81;

}

float MBRead::GetU82()
{
    while(mLocker){;}
    mLocker=true;
    float u82=(float)((mRXBuffer[3 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[3 * 2 + 1408])/1000;
    mLocker=false;
    return u82;

}

float MBRead::GetU12()
{
    while(mLocker){;}
    mLocker=true;
    float u12=(float)((mRXBuffer[4 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[1 * 2 + 1408])/1000;
    mLocker=false;
    return u12;

}

float MBRead::GetU48()
{
    while(mLocker){;}
    mLocker=true;
    float u48=(float)((mRXBuffer[5 * 2 + 1409] << 8) + (unsigned char)mRXBuffer[1 * 2 + 1408])/100;
    mLocker=false;
    return u48;

}

//получение данных о токах источников питания
float MBRead::GetI61()
{
    while(mLocker){;}
    mLocker=true;
    float i61=(float)((mRXBuffer[0 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[0 * 2 + 12 + 1408])/1000;
    mLocker=false;
    return i61;

}

float MBRead::GetI62()
{
    while(mLocker){;}
    mLocker=true;
    float i62=(float)((mRXBuffer[1 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[1 * 2 + 12 + 1408])/1000;
    mLocker=false;
    return i62;

}

float MBRead::GetI81()
{
    while(mLocker){;}
    mLocker=true;
    float i81=(float)((mRXBuffer[2 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[2 * 2 + 12 + 1408])/1000;
    mLocker=false;
    return i81;

}

float MBRead::GetI82()
{
    while(mLocker){;}
    mLocker=true;
    float i82=(float)((mRXBuffer[3 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[3 * 2 + 12 + 1408])/1000;
    mLocker=false;
    return i82;

}

float MBRead::GetI48()
{
    while(mLocker){;}
    mLocker=true;
    float i48=(float)((mRXBuffer[5 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[5 * 2 + 12 + 1408])/100;
    mLocker=false;
    return i48;

}

float MBRead::GetI12()
{
    while(mLocker){;}
    mLocker=true;
    float i12=(float)((mRXBuffer[4 * 2 + 12 + 1409] << 8) + (unsigned char)mRXBuffer[4 * 2 + 12 + 1408])/1000;
    mLocker=false;
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

bool *MBRead::GetLocker()
{
    return &mLocker;
}
