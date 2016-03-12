#ifndef ADEFINITION
#define ADEFINITION

#include <iostream>

typedef unsigned char BYTE;

struct deviceData
{
    bool isReverce; //Реверс
    short minAngle; //Мин. угол
    short maxAngle; //Макс. угол
    bool isEnable;  //Используется
    short channel;  //Номер канала
};

const uint16_t bufferSize  = 1472;
const uint16_t channelsNumber = 71;

const uint16_t SENSOR_YAW = 2;
const uint16_t SENSOR_PITCH = 4;
const uint16_t SENSOR_ROLL = 6;

const uint16_t SENSOR_UCH0 = 8;
const uint16_t SENSOR_UCH1 = 10;
const uint16_t SENSOR_UCH2 = 12;
const uint16_t SENSOR_UCH3 = 14;

const uint16_t SENSOR_TX = 8;
const uint16_t SENSOR_TY = 10;
const uint16_t SENSOR_FZ = 12;

const uint16_t DEVICE_CHANNEL =  0;

const uint16_t MOTOR_STATE =     1;
const uint16_t MOTOR_ANGLE =     2;
const uint16_t MOTOR_VOLTAGE =   4;
const uint16_t MOTOR_CURRENT =   6;
const uint16_t MOTOR_SHIFT  =    6;
const uint16_t MOTOR_P_GATE =    8;
const uint16_t MOTOR_I_GATE =    10;
const uint16_t MOTOR_MIN_ANGLE = 12;
const uint16_t MOTOR_MAX_ANGLE = 14;

const uint16_t POWER_ADDRESS = 1408;

const uint16_t POWER_VOLTAGE_6_1 =   0 * 2 + POWER_ADDRESS;
const uint16_t POWER_VOLTAGE_6_2 =   1 * 2 + POWER_ADDRESS;
const uint16_t POWER_VOLTAGE_8_1 =   2 * 2 + POWER_ADDRESS;
const uint16_t POWER_VOLTAGE_8_2 =   3 * 2 + POWER_ADDRESS;
const uint16_t POWER_VOLTAGE_12 =    4 * 2 + POWER_ADDRESS;
const uint16_t POWER_VOLTAGE_48 =    5 * 2 + POWER_ADDRESS;

const uint16_t POWER_CURRENT_6_1 =   0 * 2 + 12 + POWER_ADDRESS;
const uint16_t POWER_CURRENT_6_2 =   1 * 2 + 12 + POWER_ADDRESS;
const uint16_t POWER_CURRENT_8_1 =   2 * 2 + 12 + POWER_ADDRESS;
const uint16_t POWER_CURRENT_8_2 =   3 * 2 + 12 + POWER_ADDRESS;
const uint16_t POWER_CURRENT_12 =    4 * 2 + 12 + POWER_ADDRESS;
const uint16_t POWER_CURRENT_48 =    5 * 2 + 12 + POWER_ADDRESS;

#endif // ADEFINITION

