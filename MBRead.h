#pragma once
#include <iostream>
#include <map>
#include <stdlib.h>

class MBRead
{
private:
    char RXBUFF [1472];
    std::map<int,bool> mReverceMap;
public:
    MBRead(void);
    ~MBRead(void);

    void init(const char BUFF_other[]);

	short SENSOR_YAW_get(short NOMB);//получить данные с сенсора рысканья
	short SENSOR_PITCH_get(short NOMB);
	short SENSOR_ROLL_get(short NOMB);//получить данные с сенсора вращения/крена
	short SENSOR_UCH0_get(short NOMB);
	short SENSOR_UCH1_get(short NOMB);
	short SENSOR_UCH2_get(short NOMB);
	short SENSOR_UCH3_get(short NOMB);
	short SENSOR_TX_get(short NOMB);
	short SENSOR_TY_get(short NOMB);
	short SENSOR_FZ_get(short NOMB);

    float MOTOR_IMOT_get(short NOMB);
	short MOTOR_UBATT_get(short NOMB);
    short MOTOR_CPOS_get(short NOMB);//получить текущую позицию мотора
	short MOTOR_STIFF_get(short NOMB);//получить KP
	short MOTOR_DAMP_get(short NOMB);//получить KI
    short MOTOR_STAT_get(short NOMB);//получить статус мотора
	short MOTOR_POS_MIN_get(short NOMB);//получить минимальную позицию мотора
	short MOTOR_POS_MAX_get(short NOMB);//получить максималную позицию мотора
    float MOTOR_U_get(short NOMB);//получить напряжение мотора
    float MOTOR_I_get(short NOMB);//полусить ток мотора

    float GetU61();
    float GetU62();
    float GetU81();
    float GetU82();
    float GetU48();
    float GetU12();

    float GetI61();
    float GetI62();
    float GetI81();
    float GetI82();
    float GetI48();
    float GetI12();

    std::map<int, bool> &GetReverceMap();
    void SetReverceMap(std::map<int, bool> ReverceMap);


};

