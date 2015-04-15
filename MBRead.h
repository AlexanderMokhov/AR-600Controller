#pragma once
#include <iostream>
#include <map>
#include <stdlib.h>

class MBRead
{
private:
    char mRXBuffer [1472];
    std::map<int,bool> mReverceMap;
    std::map<int,int> mMaxPosMap;
    std::map<int,int> mMinPosMap;
public:
    MBRead(void);
    ~MBRead(void);

    void Init(const char BUFF_other[]);

    short Get_SENSOR_YAW(short NOMB);//получить данные с сенсора рысканья
    short Get_SENSOR_PITCH(short NOMB);
    short Get_SENSOR_ROLL(short NOMB);//получить данные с сенсора вращения/крена
    short Get_SENSOR_UCH0(short NOMB);
    short Get_SENSOR_UCH1(short NOMB);
    short Get_SENSOR_UCH2(short NOMB);
    short Get_SENSOR_UCH3(short NOMB);
    short Get_SENSOR_TX(short NOMB);
    short Get_SENSOR_TY(short NOMB);
    short Get_SENSOR_FZ(short NOMB);

    short Get_MOTOR_IMOT(short NOMB);
    short Get_MOTOR_UBATT(short NOMB);
    short Get_MOTOR_CPOS(short NOMB);//получить текущую позицию мотора
    short Get_MOTOR_STIFF(short NOMB);//получить KP
    short Get_MOTOR_DAMP(short NOMB);//получить KI
    short Get_MOTOR_STAT(short NOMB);//получить статус мотора
    short Get_MOTOR_MIN_POS(short NOMB);//получить минимальную позицию мотора
    short Get_MOTOR_MAX_POS(short NOMB);//получить максималную позицию мотора
    float Get_MOTOR_U(short NOMB);//получить напряжение мотора
    float Get_MOTOR_I(short NOMB);//полусить ток мотора

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

    std::map<int, bool> *GetReverceMap();
    void SetReverceMap(std::map<int, bool> *ReverceMap);
    void SetMinPosMap(std::map<int, int> *MinPosMap);
    void SetMaxPosMap(std::map<int, int> *MaxPosMap);
    const char *GetBuffer();
};

