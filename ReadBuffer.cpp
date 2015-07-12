#include "ReadBuffer.h"


ReadBuffer::ReadBuffer(void)
{

}


ReadBuffer::~ReadBuffer(void)
{

}

//инициализируем (читаем)
void ReadBuffer::Init(const char RAW_other[])
{
    mLocker.lock();
    for(int i=0;i<1472;i++)
	{
        mRAW[i]=RAW_other[i];
    }
    mLocker.unlock();
}

void ReadBuffer::SetDeviceChannel(short NumberDevice, short NumberChannel)
{
    mMotorData[NumberDevice].Channel = NumberChannel;
}

void ReadBuffer::SetMotorReverce(short Number, bool value)
{
    mMotorData[Number].isReverce = value;

}

short ReadBuffer::GetSensorYaw(short Number)
{
    mLocker.lock();
    short sensor_yaw =(mRAW[mMotorData[Number].Channel*16+3] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+2];
    mLocker.unlock();
    return sensor_yaw;
}

short ReadBuffer::GetSensorPitch(short Number)
{
    mLocker.lock();
    short sensor_pitch = (mRAW[mMotorData[Number].Channel*16+5] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+4];
    mLocker.unlock();
    return sensor_pitch;
}

short ReadBuffer::GetSensorRoll(short Number)
{
    mLocker.lock();
    short sensor_roll=(mRAW[mMotorData[Number].Channel*16+7] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+6];
    mLocker.unlock();
    return sensor_roll;
}

short ReadBuffer::GetSensorUCH0(short Number)
{
    mLocker.lock();
    short sensor_uch0=(mRAW[mMotorData[Number].Channel*16+9] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+8];
    mLocker.unlock();
    return sensor_uch0;
}

short ReadBuffer::GetSensorUCH1(short Number)
{
    mLocker.lock();
    short sensor_uch1=(mRAW[mMotorData[Number].Channel*16+11] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+10];
    mLocker.unlock();
    return sensor_uch1;
}

short ReadBuffer::GetSensorUCH2(short Number)
{
    mLocker.lock();
    short sensor_uch2=(mRAW[mMotorData[Number].Channel*16+13] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+12];
    mLocker.unlock();
    return sensor_uch2;
}

short ReadBuffer::GetSensorUCH3(short Number)
{
    mLocker.lock();
    short sensor_uch3=(mRAW[mMotorData[Number].Channel*16+15] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+14];
    mLocker.unlock();
    return sensor_uch3;
}

short ReadBuffer::GetSensorTX(short Number)
{
    mLocker.lock();
    short sensor_tx=(mRAW[mMotorData[Number].Channel*16+3] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+2];
    mLocker.unlock();
    return sensor_tx;
}

short ReadBuffer::GetSensorTY(short Number)
{
    mLocker.lock();
    short sensor_ty=(mRAW[mMotorData[Number].Channel*16+5] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+4];
    mLocker.unlock();
    return sensor_ty;
}

short ReadBuffer::GetSensorFZ(short Number)
{
    mLocker.lock();
    short sensor_fz=(mRAW[mMotorData[Number].Channel*16+7] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+6];
    mLocker.unlock();
    return sensor_fz;
}

short ReadBuffer::GetSensorValue(short Number, int Param)
{
    switch(Number)
    {
        case 14:
            switch(Param)
            {
                case 1:
                {
                    return GetSensorTX(Number);
                }
                break;
                case 2:
                {
                    return GetSensorTY(Number);
                }
                break;
                case 3:
                {
                    return GetSensorFZ(Number);
                }
                break;
                case 4:
                {
                    return GetSensorYaw(Number);
                }
                break;
                case 5:
                {
                    return GetSensorPitch(Number);
                }
                break;
                case 6:
                {
                    return GetSensorRoll(Number);
                }
                break;
            }
        break;
        default:
            switch(Param)
            {
                case 1:
                {
                    return GetSensorUCH0(Number);
                }
                break;
                case 2:
                {
                    return GetSensorUCH1(Number);
                }
                break;
                case 3:
                {
                    return GetSensorUCH2(Number);
                }
                break;
                case 4:
                {
                    return GetSensorUCH3(Number);
                }
                break;
            }
        break;
    }
}

short ReadBuffer::GetMotorU(short Number)
{
    mLocker.lock();
    short motor_ubatt=(mRAW[mMotorData[Number].Channel*16+5] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+4];
    mLocker.unlock();
    return motor_ubatt;
}

short ReadBuffer::GetMotorI(short Number)
{
    mLocker.lock();
    short motor_imot=(mRAW[mMotorData[Number].Channel*16+7] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+6];
    mLocker.unlock();
    return motor_imot;
}

short ReadBuffer::GetMotorAngle(short Number)
{
    mLocker.lock();
    short cpos = (mRAW[mMotorData[Number].Channel*16+3] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+2];
    if(mMotorData[Number].isReverce)
    {
        cpos = -1*cpos;
    }
    mLocker.unlock();
    return cpos;
}

short ReadBuffer::GetMotorStiff(short Number)
{
    mLocker.lock();
    short motor_stiff=(mRAW[mMotorData[Number].Channel*16+9] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+8];
    mLocker.unlock();
    return motor_stiff;
}

short ReadBuffer::GetMotorDamp(short Number)
{
    mLocker.lock();
    short motor_damp=(mRAW[mMotorData[Number].Channel*16+11] << 8) +
            (BYTE)mRAW[mMotorData[Number].Channel*16+10];
    mLocker.unlock();
    return motor_damp;
}

short ReadBuffer::GetMotorStatus(short Number)
{
    mLocker.lock();
    short motor_stat=(BYTE)mRAW[mMotorData[Number].Channel*16+1];
    mLocker.unlock();
    return motor_stat;

}

short ReadBuffer::GetMotorMinAngle(short Number)
{
    short minpos;
    mLocker.lock();
    if(mMotorData[Number].isReverce)
    {
        minpos = -1*((mRAW[mMotorData[Number].Channel*16+15] << 8) +
                (BYTE)mRAW[mMotorData[Number].Channel*16+14]);
    }
    else
    {
        minpos = (mRAW[mMotorData[Number].Channel*16+13] << 8) +
                (BYTE)mRAW[mMotorData[Number].Channel*16+12];
    }
    mLocker.unlock();
    return minpos;
}

short ReadBuffer::GetMotorMaxAngle(short Number)
{
    short maxpos;
    mLocker.lock();
    if(mMotorData[Number].isReverce)
    {
        maxpos = -1*((mRAW[mMotorData[Number].Channel*16+13] << 8) +
                (BYTE)mRAW[mMotorData[Number].Channel*16+12]);
    }
    else
    {
        maxpos = (mRAW[mMotorData[Number].Channel*16+15] << 8) +
                (BYTE)mRAW[mMotorData[Number].Channel*16+14];
    }
    mLocker.unlock();
    return maxpos;
}

float ReadBuffer::GetPowerU61()
{
    mLocker.lock();
    float u61=(float)((mRAW[0 * 2 + 1409] << 8) + (BYTE)mRAW[0 * 2 + 1408])/1000;
    mLocker.unlock();
    return u61;

}

float ReadBuffer::GetPowerU62()
{
    mLocker.lock();
    float u62=(float)((mRAW[1 * 2 + 1409] << 8) + (BYTE)mRAW[1 * 2 + 1408])/1000;
    mLocker.unlock();
    return u62;

}

float ReadBuffer::GetPowerU81()
{
    mLocker.lock();
    float u81=(float)((mRAW[2 * 2 + 1409] << 8) + (BYTE)mRAW[2 * 2 + 1408])/1000;
    mLocker.unlock();
    return u81;

}

float ReadBuffer::GetPowerU82()
{
    mLocker.lock();
    float u82=(float)((mRAW[3 * 2 + 1409] << 8) + (BYTE)mRAW[3 * 2 + 1408])/1000;
    mLocker.unlock();
    return u82;

}

float ReadBuffer::GetPowerU12()
{
    mLocker.lock();
    float u12=(float)((mRAW[4 * 2 + 1409] << 8) + (BYTE)mRAW[1 * 2 + 1408])/1000;
    mLocker.unlock();
    return u12;

}

float ReadBuffer::GetPowerU48()
{
    mLocker.lock();
    float u48=(float)((mRAW[5 * 2 + 1409] << 8) + (BYTE)mRAW[1 * 2 + 1408])/100;
    mLocker.unlock();
    return u48;

}

float ReadBuffer::GetPowerI61()
{
    mLocker.lock();
    float i61=(float)((mRAW[0 * 2 + 12 + 1409] << 8) + (BYTE)mRAW[0 * 2 + 12 + 1408])/1000;
    mLocker.unlock();
    return i61;

}

float ReadBuffer::GetPowerI62()
{
    mLocker.lock();
    float i62=(float)((mRAW[1 * 2 + 12 + 1409] << 8) + (BYTE)mRAW[1 * 2 + 12 + 1408])/1000;
    mLocker.unlock();
    return i62;
}

float ReadBuffer::GetPowerI81()
{
    mLocker.lock();
    float i81=(float)((mRAW[2 * 2 + 12 + 1409] << 8) + (BYTE)mRAW[2 * 2 + 12 + 1408])/1000;
    mLocker.unlock();
    return i81;

}

float ReadBuffer::GetPowerI82()
{
    mLocker.lock();
    float i82=(float)((mRAW[3 * 2 + 12 + 1409] << 8) + (BYTE)mRAW[3 * 2 + 12 + 1408])/1000;
    mLocker.unlock();
    return i82;

}

float ReadBuffer::GetPowerI48()
{
    mLocker.lock();
    float i48=(float)((mRAW[5 * 2 + 12 + 1409] << 8) + (BYTE)mRAW[5 * 2 + 12 + 1408])/100;
    mLocker.unlock();
    return i48;

}

float ReadBuffer::GetPowerI12()
{
    mLocker.lock();
    float i12=(float)((mRAW[4 * 2 + 12 + 1409] << 8) + (BYTE)mRAW[4 * 2 + 12 + 1408])/1000;
    mLocker.unlock();
    return i12;

}

const char *ReadBuffer::GetRAW()
{
    return mRAW;
}

std::mutex *ReadBuffer::GetLocker()
{
    return &mLocker;
}
