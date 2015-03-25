#pragma once
class MBWrite
{

private:
    char WRBUFF[1472];
public:
	MBWrite(void);
	~MBWrite(void);



	void init(unsigned char BUFF_other[]);
	void init(void);
    void DebugPrint();
    const char *GetBuffer();
    unsigned int GetSize()
    {
        return 1472;
    }

	//датчик усилия
	void SENSOR_UCH0_set(short NOMB, short value);
	void SENSOR_UCH1_set(short NOMB, short value);
	void SENSOR_UCH2_set(short NOMB, short value);
	void SENSOR_UCH3_set(short NOMB, short value);

	void SENSOR_OFFSET(short NOMB, unsigned char RXBUFF[]);
	void SENSOR_XY_OFFSET(short NOMB, unsigned char RXBUFF[]);
	void SENSOR_Z_OFFSET(short NOMB, unsigned char RXBUFF[]);

	void MOTOR_ANGLE_set(short NOMB, short value);
	void MOTOR_ILIM_set(short NOMB, short value);
	void MOTOR_STIFF_set(short NOMB, short value);
	void MOTOR_DAMP_set(short NOMB, short value);
	void MOTOR_POS_MIN_set(short NOMB, short value);
	void MOTOR_POS_MAX_set(short NOMB, short value);
	void MOTOR_CENTER(short NOMB, unsigned char RXBUFF[]);
	void MOTOR_STOP(short NOMB);
	void MOTOR_TRACE(short NOMB);
	void MOTOR_RELAX(short NOMB);
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
    void AddressUpdate(short number, short buffAddr);

};

