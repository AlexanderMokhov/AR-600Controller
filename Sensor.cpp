#include "Sensor.h"

Sensor::Sensor()
{
    mValue = 0;
}

Sensor::~Sensor()
{

}

Sensor::Sensor(unsigned int Number,
               unsigned int NumberBuffer,
               string Name,
               string NameLog,
               int param): Device(Number,NumberBuffer,Name)
{
    mParam = param;
    mValue = 0;
    mNameLog = NameLog;
}

int Sensor::GetValue()
{
    switch(mNumberBuffer)
    {
        case 14:
            switch(mParam)
            {
                case 1:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_TX(mNumberBuffer);
                }
                break;
                case 2:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_TY(mNumberBuffer);
                }
                break;
                case 3:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_FZ(mNumberBuffer);
                }
                break;
                case 4:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_YAW(mNumberBuffer);
                }
                break;
                case 5:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_PITCH(mNumberBuffer);
                }
                break;
                case 6:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_ROLL(mNumberBuffer);
                }
                break;
            }
        break;
        default:
            switch(mParam)
            {
                case 1:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_UCH0(mNumberBuffer);
                }
                break;
                case 2:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_UCH1(mNumberBuffer);
                }
                break;
                case 3:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_UCH2(mNumberBuffer);
                }
                break;
                case 4:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_UCH3(mNumberBuffer);
                }
                break;
            }
        break;
    }
}

void Sensor::SetValue(int value)
{
    switch(mNumberBuffer)
    {
        case 14:
        break;
        default:
            switch(mParam)
            {
                case 1:
                {
                    return BufferController::Instance()->GetWriteBuffer()->Set_SENSOR_UCH0(mNumberBuffer,value);
                }
                break;
                case 2:
                {
                    return BufferController::Instance()->GetWriteBuffer()->Set_SENSOR_UCH1(mNumberBuffer,value);
                }
                break;
                case 3:
                {
                    return BufferController::Instance()->GetWriteBuffer()->Set_SENSOR_UCH2(mNumberBuffer,value);
                }
                break;
                case 4:
                {
                    return BufferController::Instance()->GetWriteBuffer()->Set_SENSOR_UCH3(mNumberBuffer,value);
                }
                break;
            }
        break;
    }
}

string Sensor::GetNameLog()
{
    return mNameLog;
}

void Sensor::SetNameLog(string NameLog)
{
    mNameLog = NameLog;
}

int Sensor::GetParam()
{
    return mParam;
}

void Sensor::SetParam(int Param)
{
    mParam = Param;
}

