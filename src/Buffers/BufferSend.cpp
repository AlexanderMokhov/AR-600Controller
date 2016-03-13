#include "BufferSend.h"

#include <stdio.h>
#include <QDebug>


void BufferSend::writeInt16(uint16_t address, int16_t value)
{
    m_RAW[address + 1] = (BYTE)(value >> 8);
    m_RAW[address] = value;
}

BufferSend::BufferSend(void)
{
    for(int i = 0; i < bufferSize; i++) m_RAW[i] = 0;
    onPower12();
}


BufferSend::~BufferSend(void)
{

}

//инициализируем (читаем)
void BufferSend::initialize(unsigned char RAW_other[])
{
    m_locker.lock();
    for(int i = 0; i < bufferSize; i++)  m_RAW[i] = RAW_other[i];
    m_locker.unlock();
}

//инициализируем (установка 12 В)
void BufferSend::initialize(void)
{
    m_locker.lock();
    for(int i = 0; i < bufferSize; i++) m_RAW[i] = 0;
    onPower12();
    m_locker.unlock();
}

const char *BufferSend::getRAW()
{
    return m_RAW;
}

//установка питания

//включить 6 В (1)
void BufferSend::onPower6_1(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] |= 1;
    m_locker.unlock();
}

//включить 6 В (2)
void BufferSend::onPower6_2(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] |= 2;
    m_locker.unlock();
}

//включить 8 В (1)
void BufferSend::onPower8_1(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] |= 4;
    m_locker.unlock();
}

//включить 8 В (2)
void BufferSend::onPower8_2(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] |= 8;
    m_locker.unlock();
}

//включить 12 В
void BufferSend::onPower12(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] |= 16;
    m_locker.unlock();
}

//включить 48 В
void BufferSend::onPower48(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] |= 32;
    m_locker.unlock();
}

//выключить 6 В (1)
void BufferSend::offPower6_1(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] &= (255-1);
    m_locker.unlock();
}

//выключить 6 В (2)
void BufferSend::offPower6_2(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] &= (255-2);
    m_locker.unlock();
}

//выключить 8 В (1)
void BufferSend::offPower8_1(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] &= (255-4);
    m_locker.unlock();
}

//выключить 8 В (2)
void BufferSend::offPower8_2(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] &= (255-8);
    m_locker.unlock();
}

//выключить 12 В
void BufferSend::offPower12(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] &= (255-16);
    m_locker.unlock();
}

//выключить 48 В
void BufferSend::offPower48(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] &= (255-32);
    m_locker.unlock();
}

//включить беззвучный режим
void BufferSend::onMute(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] |= 128;
    m_locker.unlock();
}

//выключить беззвучный режим
void BufferSend::offMute(void)
{
    m_locker.lock();
    m_RAW[POWER_ADDRESS + 1] &= (255-128);
    m_locker.unlock();
}

void BufferSend::setDeviceChannel(short NumberDevice, short NumberChannel)
{
    m_motorsData[NumberDevice].channel = NumberChannel;
    m_locker.lock();
    writeInt16(NumberChannel * 16, NumberDevice);
    m_locker.unlock();
}

std::mutex *BufferSend::getLocker()
{
    return &m_locker;
}

//установка значений сенсоров

void BufferSend::setSensorUCH0(short Number, short value)
{
    m_locker.lock();
    writeInt16(m_motorsData[Number].channel * 16 + SENSOR_UCH0, value);
    m_locker.unlock();
}

void BufferSend::setSensorUCH1(short Number, short value)
{
    m_locker.lock();
    writeInt16(m_motorsData[Number].channel * 16 + SENSOR_UCH1, value);
    m_locker.unlock();
}

void BufferSend::setSensorUCH2(short Number, short value)
{
    m_locker.lock();
    writeInt16(m_motorsData[Number].channel * 16 + SENSOR_UCH2, value);
    m_locker.unlock();
}

void BufferSend::setSensorUCH3(short Number, short value)
{
    m_locker.lock();
    writeInt16(m_motorsData[Number].channel * 16 + SENSOR_UCH3, value);
    m_locker.unlock();
}
//установка значений моторов

//повернуть мотор на угол
void BufferSend::setMotorAngle(short Number, short value)
{
    short minAngle = m_motorsData[Number].minAngle;
    short maxAngle = m_motorsData[Number].maxAngle;
    if(value < minAngle)
    {
        qDebug() << QString::number(Number) << " !!!Значение" << QString::number(value)
                 << "ниже минимума" << QString::number(minAngle) << endl;
        value = minAngle;

    }
    else if(value > maxAngle)
    {
        qDebug() << QString::number(Number) << " !!!Значение" << QString::number(value)
                 << "выше максимума" << QString::number(maxAngle) << endl;
        value = maxAngle;

    }
    if(m_motorsData[Number].isReverce) value = -1 * value;
    m_locker.lock();
    writeInt16(m_motorsData[Number].channel * 16 + MOTOR_ANGLE, value);
    m_locker.unlock();
}

void BufferSend::setMotorShiftValue(short Number, short value)
{
    m_locker.lock();
    writeInt16(m_motorsData[Number].channel * 16 + MOTOR_SHIFT, value);
    m_locker.unlock();
}

void BufferSend::setMotorPGate(short Number, short value)
{
    m_locker.lock();
    writeInt16(m_motorsData[Number].channel * 16 + MOTOR_P_GATE, value);
    m_locker.unlock();
}

void BufferSend::setMotorIGate(short Number, short value)
{
    m_locker.lock();
    writeInt16(m_motorsData[Number].channel *16 + MOTOR_I_GATE, value);
    m_locker.unlock();
}

void BufferSend::setMotorDGate(short Number, short value)
{
    m_locker.lock();
    writeInt16(m_motorsData[Number].channel * 16 + MOTOR_D_GATE, value);
    m_locker.unlock();
}

void BufferSend::setMotorMinAngle(short Number, short value)
{
    m_motorsData[Number].minAngle = value;//запоминаем отображаемое значение
    m_locker.lock();
    if(m_motorsData[Number].isReverce)
        writeInt16(m_motorsData[Number].channel * 16 + MOTOR_MAX_ANGLE, -1 * value);
    else
        writeInt16(m_motorsData[Number].channel * 16 + MOTOR_MIN_ANGLE, value);
    m_locker.unlock();
}

void BufferSend::setMotorMaxAngle(short Number, short value)
{
    m_motorsData[Number].maxAngle = value;//запоминаем отображаемое значение
    m_locker.lock();
    if(m_motorsData[Number].isReverce)
        writeInt16(m_motorsData[Number].channel * 16 + MOTOR_MIN_ANGLE, -1 * value);
    else
        writeInt16(m_motorsData[Number].channel * 16 + MOTOR_MAX_ANGLE, value);
    m_locker.unlock();
}

void BufferSend::setMotorEnable(short Number, bool value)
{
    m_motorsData[Number].isEnable = value;
}

void BufferSend::setMotorReverceState(short Number, bool value)
{
    m_motorsData[Number].isReverce = value;
}

//остановить мотор
void BufferSend::motorStop(short Number)
{
    m_locker.lock();
    m_RAW[m_motorsData[Number].channel * 16 + 1] &= (255 - 3);
    m_RAW[m_motorsData[Number].channel * 16 + 1] |= 1;
    m_locker.unlock();
}

//зафиксировать мотор
void BufferSend::motorTrace(short Number)
{
    m_locker.lock();
    if(m_motorsData[Number].isEnable)
        m_RAW[m_motorsData[Number].channel * 16 + 1] |= 3;
    m_locker.unlock();
}

//ослабить мотор
void BufferSend::motorRelax(short Number)
{
    m_locker.lock();
    m_RAW[m_motorsData[Number].channel * 16 + 1] &= (255 - 3);
    m_RAW[m_motorsData[Number].channel * 16 + 1] |= 2;
    m_locker.unlock();
}

//отменить остановку мотора
void BufferSend::motorStopBrake(short Number)
{
    m_locker.lock();
    m_RAW[m_motorsData[Number].channel * 16 + 1] &= (255 - 3);
    m_locker.unlock();
}

short BufferSend::getMotorDGate(short Number)
{
    m_locker.lock();
    short motor_torque=(m_RAW[m_motorsData[Number].channel*16+5] << 8) +
            (BYTE)m_RAW[m_motorsData[Number].channel*16+4];
    m_locker.unlock();
    return motor_torque;
}
