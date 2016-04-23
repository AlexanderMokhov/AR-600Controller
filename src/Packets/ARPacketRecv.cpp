#include "ARPacketRecv.h"


int16_t ARPacketRecv::readInt16(uint16_t address)
{
    int16_t value = (m_RAW[address + 1] << 8) + (BYTE)m_RAW[address];
    return value;
}

float ARPacketRecv::readFloat(uint16_t address)
{
    float value = static_cast<float>((m_RAW[address + 1] << 8) + (BYTE)m_RAW[address]);
    return value;
}

ARPacketRecv::ARPacketRecv(void)
{

}


ARPacketRecv::~ARPacketRecv(void)
{

}

//инициализируем (читаем)
void ARPacketRecv::initialize(const char RAW_other[])
{
    m_locker.lock();
    for(int i = 0; i < bufferSize; i++) m_RAW[i] = RAW_other[i];
    m_locker.unlock();
}

void ARPacketRecv::setDeviceChannel(short NumberDevice, short NumberChannel)
{
    m_motorsData[NumberDevice].channel = NumberChannel;
}

void ARPacketRecv::setMotorReverce(short Number, bool value)
{
    m_motorsData[Number].isReverce = value;

}

short ARPacketRecv::getSensorYaw(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + SENSOR_YAW);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getSensorPitch(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + SENSOR_PITCH);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getSensorRoll(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + SENSOR_ROLL);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getSensorUCH0(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + SENSOR_UCH0);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getSensorUCH1(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + SENSOR_UCH1);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getSensorUCH2(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + SENSOR_UCH2);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getSensorUCH3(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + SENSOR_UCH3);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getSensorTX(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + SENSOR_TX);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getSensorTY(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + SENSOR_TY);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getSensorFZ(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + SENSOR_FZ);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getSensorValue(short Number, int Param)
{
    switch(Number)
    {
        case 14:
            switch(Param)
            {
                case 1:
                {
                    return getSensorTX(Number);
                }
                break;
                case 2:
                {
                    return getSensorTY(Number);
                }
                break;
                case 3:
                {
                    return getSensorFZ(Number);
                }
                break;
                case 4:
                {
                    return getSensorYaw(Number);
                }
                break;
                case 5:
                {
                    return getSensorPitch(Number);
                }
                break;
                case 6:
                {
                    return getSensorRoll(Number);
                }
                break;
            }
        break;
        default:
            switch(Param)
            {
                case 1:
                {
                    return getSensorUCH0(Number);
                }
                break;
                case 2:
                {
                    return getSensorUCH1(Number);
                }
                break;
                case 3:
                {
                    return getSensorUCH2(Number);
                }
                break;
                case 4:
                {
                    return getSensorUCH3(Number);
                }
                break;
            }
        break;
    }
}

short ARPacketRecv::getMotorVoltage(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + MOTOR_VOLTAGE);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getMotorCurrent(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + MOTOR_CURRENT);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getMotorAngle(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + MOTOR_ANGLE);
    if(m_motorsData[Number].isReverce) value = -1 * value;
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getMotorPGate(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + MOTOR_P_GATE);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getMotorIGate(short Number)
{
    m_locker.lock();
    int16_t value = readInt16(m_motorsData[Number].channel * 16 + MOTOR_I_GATE);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getMotorState(short Number)
{
    m_locker.lock();
    int16_t value = (BYTE)m_RAW[m_motorsData[Number].channel*16+1];
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getMotorMinAngle(short Number)
{
    int16_t value;
    m_locker.lock();
    if(m_motorsData[Number].isReverce)
        value = -1 * readInt16(m_motorsData[Number].channel * 16 + MOTOR_MAX_ANGLE);
    else
        value = readInt16(m_motorsData[Number].channel * 16 + MOTOR_MIN_ANGLE);
    m_locker.unlock();
    return value;
}

short ARPacketRecv::getMotorMaxAngle(short Number)
{
    int16_t value;
    m_locker.lock();
    if(m_motorsData[Number].isReverce)
        value = -1 * readInt16(m_motorsData[Number].channel * 16 + MOTOR_MIN_ANGLE);
    else
        value = readInt16(m_motorsData[Number].channel * 16 + MOTOR_MAX_ANGLE);
    m_locker.unlock();
    return value;
}

float ARPacketRecv::getPowerVoltage6_1()
{
    m_locker.lock();
    float value = readFloat(POWER_VOLTAGE_6_1) / 1000;
    m_locker.unlock();
    return value;
}

float ARPacketRecv::getPowerVoltage6_2()
{
    m_locker.lock();
    float value = readFloat(POWER_VOLTAGE_6_2) / 1000;
    m_locker.unlock();
    return value;
}

float ARPacketRecv::getPowerVoltage8_1()
{
    m_locker.lock();
    float value = readFloat(POWER_VOLTAGE_8_1) / 1000;
    m_locker.unlock();
    return value;
}

float ARPacketRecv::getPowerVoltage8_2()
{
    m_locker.lock();
    float value = readFloat(POWER_VOLTAGE_8_2) / 1000;
    m_locker.unlock();
    return value;
}

float ARPacketRecv::getPowerVoltage12()
{
    m_locker.lock();
    float value = readFloat(POWER_VOLTAGE_12) / 1000;
    m_locker.unlock();
    return value;
}

float ARPacketRecv::getPowerVoltage48()
{
    m_locker.lock();
    float value = readFloat(POWER_VOLTAGE_48) / 100;
    m_locker.unlock();
    return value;
}

float ARPacketRecv::getPowerCurrent6_1()
{
    m_locker.lock();
    float value = readFloat(POWER_CURRENT_6_1) / 1000;
    m_locker.unlock();
    return value;
}

float ARPacketRecv::getPowerCurrent6_2()
{
    m_locker.lock();
    float value = readFloat(POWER_CURRENT_6_2) / 1000;
    m_locker.unlock();
    return value;
}

float ARPacketRecv::getPowerCurrent8_1()
{
    m_locker.lock();
    float value = readFloat(POWER_CURRENT_8_1) / 1000;
    m_locker.unlock();
    return value;
}

float ARPacketRecv::getPowerCurrent8_2()
{
    m_locker.lock();
    float value = readFloat(POWER_CURRENT_8_2) / 1000;
    m_locker.unlock();
    return value;
}

float ARPacketRecv::getPowerCurrent48()
{
    m_locker.lock();
    float value = readFloat(POWER_CURRENT_48) / 100;
    m_locker.unlock();
    return value;
}

float ARPacketRecv::getPowerCurrent12()
{
    m_locker.lock();
    float value = readFloat(POWER_CURRENT_12) / 1000;
    m_locker.unlock();
    return value;
}

const char *ARPacketRecv::getRAW()
{
    return m_RAW;
}

std::mutex *ARPacketRecv::getLocker()
{
    return &m_locker;
}
