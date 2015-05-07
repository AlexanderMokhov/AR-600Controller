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
               int param): Device(Number,NumberBuffer,Name)
{
    mParam = param;
    mValue = 0;
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
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_TX(mNumber);
                }
                break;
                case 2:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_TY(mNumber);
                }
                break;
                case 3:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_FZ(mNumber);
                }
                break;
                case 4:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_YAW(mNumber);
                }
                break;
                case 5:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_PITCH(mNumber);
                }
                break;
                case 6:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_ROLL(mNumber);
                }
                break;
            }
        break;
        default:
            switch(mParam)
            {
                case 1:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_UCH0(mNumber);
                }
                break;
                case 2:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_UCH1(mNumber);
                }
                break;
                case 3:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_UCH2(mNumber);
                }
                break;
                case 4:
                {
                    return BufferController::Instance()->GetReadBuffer()->Get_SENSOR_UCH3(mNumber);
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
                    return BufferController::Instance()->GetWriteBuffer()->Set_SENSOR_UCH0(mNumber,value);
                }
                break;
                case 2:
                {
                    return BufferController::Instance()->GetWriteBuffer()->Set_SENSOR_UCH1(mNumber,value);
                }
                break;
                case 3:
                {
                    return BufferController::Instance()->GetWriteBuffer()->Set_SENSOR_UCH2(mNumber,value);
                }
                break;
                case 4:
                {
                    return BufferController::Instance()->GetWriteBuffer()->Set_SENSOR_UCH3(mNumber,value);
                }
                break;
            }
        break;
    }
}

