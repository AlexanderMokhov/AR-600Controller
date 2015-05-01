#pragma once
#include <iostream>
#include <map>
#include <mutex>
#include <stdlib.h>

class MBWrite
{
private:
    char mWRBuffer [1472];
    std::map<int,bool> mReverceMap;
    std::map<int,int> mMaxPosMap;
    std::map<int,int> mMinPosMap;
    std::map<int,bool> mEnableMap;
    short mMinPos;
    short mMaxPos;
    std::mutex mLocker;

public:
	MBWrite(void);
	~MBWrite(void);

    void Init(unsigned char BUFF_other[]);
    void Init(void);
    void DebugPrint();
    const char *GetBuffer();
    unsigned int GetSize()
    {
        return 1472;
    }

	//датчик усилия
    void Set_SENSOR_UCH0(short NOMB, short value);
    void Set_SENSOR_UCH1(short NOMB, short value);
    void Set_SENSOR_UCH2(short NOMB, short value);
    void Set_SENSOR_UCH3(short NOMB, short value);

    void SENSOR_OFFSET(short NOMB,const char RXBuffer[]);
    void SENSOR_XY_OFFSET(short NOMB,const char RXBuffer[]);
    void SENSOR_Z_OFFSET(short NOMB,const char RXBuffer[]);

    void Set_MOTOR_ANGLE(short NOMB, short value);
    void Set_MOTOR_CALIBRATION(short NOMB, short value);
    void Set_MOTOR_STIFF(short NOMB, short value);//установить KP
    void Set_MOTOR_DAMP(short NOMB, short value);//установить KI
    void Set_MOTOR_MIN_POS(short NOMB, short value);
    void Set_MOTOR_MAX_POS(short NOMB, short value);
    void MOTOR_CENTER(short NOMB, unsigned char RXBuffer[]);//без фиксации - динамическое торможение
    void MOTOR_STOP(short NOMB);//режим фиксации
    void MOTOR_TRACE(short NOMB);//режим следование за положением
	void MOTOR_RELAX(short NOMB);//убрать фиксацию мотора
	void MOTOR_STOP_BR(short NOMB);
	void MOTOR_SET_REVERS(short NOMB);
	void MOTOR_CLR_REVERS(short NOMB);

	void ON61(void);
	void ON62(void);
	void ON81(void);
	void ON82(void);
	void ON12(void);
	void ON48(void);

	void OFF61(void);
	void OFF62(void);
	void OFF81(void);
	void OFF82(void);
	void OFF12(void);
	void OFF48(void);

	void MUTE_ON(void);
	void MUTE_OFF(void);

    // add number of channel in sender buffer
    //добавить номер канала в отправляемый буфер
    void AddressUpdate(short NOMB, short NumberMotor);

    std::map<int, bool> *GetReverceMap();
    std::map<int, int> *GetMinPosMap();
    std::map<int, int> *GetMaxPosMap();
    std::map<int, bool> *GetEnableMap();
    std::mutex *GetLocker();

};

