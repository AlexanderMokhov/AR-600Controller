#include "MBRead.h"


MBRead::MBRead(void)
{
}


MBRead::~MBRead(void)
{
}

//инициализируем (читаем)
void MBRead::init(const char BUFF_other[])
{
    for(int i=0;i<1472;i++)
	{
		RXBUFF[i]=BUFF_other[i];
	}
}

//получение данных с сенсоров
#pragma region Sensor

//получить данные с сенсора рысканья
short MBRead::SENSOR_YAW_get(short NOMB)
{
	return (RXBUFF[NOMB*16+3] << 8) + RXBUFF[NOMB*16+2];
}

short MBRead::SENSOR_PITCH_get(short NOMB)
{
	return (RXBUFF[NOMB*16+5] << 8) + RXBUFF[NOMB*16+4];
}

//получить данные с сенсора вращения/крена
short MBRead::SENSOR_ROLL_get(short NOMB)
{
	return (RXBUFF[NOMB*16+7] << 8) + RXBUFF[NOMB*16+6];
}

short MBRead::SENSOR_UCH0_get(short NOMB)
{
	return (RXBUFF[NOMB*16+9] << 8) + RXBUFF[NOMB*16+8];
}

short MBRead::SENSOR_UCH1_get(short NOMB)
{
	return (RXBUFF[NOMB*16+11] << 8) + RXBUFF[NOMB*16+10];
}

short MBRead::SENSOR_UCH2_get(short NOMB)
{
	return (RXBUFF[NOMB*16+13] << 8) + RXBUFF[NOMB*16+12];
}

short MBRead::SENSOR_UCH3_get(short NOMB)
{
	return (RXBUFF[NOMB*16+15] << 8) + RXBUFF[NOMB*16+14];
}

short MBRead::SENSOR_TX_get(short NOMB)
{
	return (RXBUFF[NOMB*16+3] << 8) + RXBUFF[NOMB*16+2];
}

short MBRead::SENSOR_TY_get(short NOMB)
{
	return (RXBUFF[NOMB*16+5] << 8) + RXBUFF[NOMB*16+4];
}

short MBRead::SENSOR_FZ_get(short NOMB)
{
	return (RXBUFF[NOMB*16+7] << 8) + RXBUFF[NOMB*16+6];
}

#pragma endregion Sensor

//получение данных с моторов
#pragma region Motor

//получить напряжение питания мотора
short MBRead::MOTOR_UBATT_get(short NOMB)
{
	return (RXBUFF[NOMB*16+7] << 8) + RXBUFF[NOMB*16+6];
}

//получить ток, потребляемый мотором
short MBRead::MOTOR_IMOT_get(short NOMB)
{
	return (RXBUFF[NOMB*16+5] << 8) + RXBUFF[NOMB*16+4];
}

//получить текщую позицию мотора
short MBRead::MOTOR_CPOS_get(short NOMB)
{
    return (short) ((RXBUFF[NOMB*16+3] << 8) + (RXBUFF[NOMB*16+2]));
}

//получить KP
short MBRead::MOTOR_STIFF_get(short NOMB)
{
	return (RXBUFF[NOMB*16+9] << 8) + RXBUFF[NOMB*16+8];
}

//получить KI
short MBRead::MOTOR_DAMP_get(short NOMB)
{
	short MOTOR_DUMP = (RXBUFF[NOMB*16+11] << 8) + RXBUFF[NOMB*16+10];
	return MOTOR_DUMP;
}

//получить статус мотора
char MBRead::MOTOR_STAT_get(short NOMB)
{
    return RXBUFF[NOMB*16+1];
}

//получить минимальную позицию мотора
short MBRead::MOTOR_POS_MIN_get(short NOMB)
{
	return (RXBUFF[NOMB*16+13] << 8) + RXBUFF[NOMB*16+12];
}

//получить максимальную позицию мотора
short MBRead::MOTOR_POS_MAX_get(short NOMB)
{
	return (RXBUFF[NOMB*16+15] << 8) + RXBUFF[NOMB*16+14];
}

//получить напряжение мотора
float MBRead::MOTOR_U_get(short NOMB)
{
    return (float)((RXBUFF[NOMB*2+1409] << 8) + RXBUFF[NOMB*2+1408]);
}

//получить ток мотора
float MBRead::MOTOR_I_get(short NOMB)
{
    return float((RXBUFF[NOMB*2+12+1409] << 8) + RXBUFF[NOMB*2+12+1408]);
}

//получение данных о напряжении источников питания
float MBRead::GetU61()
{
    return (float)((RXBUFF[0 * 2 + 1409] << 8) + RXBUFF[0 * 2 + 1408])/1000;

    //Public ReadOnly Property U(NOMB As Int16) As Int16
    //       Get
    //           U = BitConverter.ToInt16(RXBUFF, NOMB * 2 + 1408)
    //       End Get
    //   End Property
    //   Public ReadOnly Property I(NOMB As Int16) As Int16
    //       Get
    //           I = BitConverter.ToInt16(RXBUFF, NOMB * 2 + 12 + 1408)
    //       End Get
    //   End Property
}

float MBRead::GetU62()
{
    return (float)((RXBUFF[1 * 2 + 1409] << 8) + RXBUFF[1 * 2 + 1408])/1000;
}

float MBRead::GetU81()
{
    return (float)((RXBUFF[2 * 2 + 1409] << 8) + RXBUFF[2 * 2 + 1408])/1000;
}

float MBRead::GetU82()
{
    return (float)((RXBUFF[3 * 2 + 1409] << 8) + RXBUFF[3 * 2 + 1408])/1000;
}

float MBRead::GetU12()
{
    return (float)((RXBUFF[4 * 2 + 1409] << 8) + RXBUFF[1 * 2 + 1408])/1000;
}

float MBRead::GetU48()
{
    return (float)((RXBUFF[5 * 2 + 1409] << 8) + RXBUFF[1 * 2 + 1408])/100;
}

//получение данных о токах источников питания
float MBRead::GetI61()
{
    return (float)((RXBUFF[0 * 2 + 12 + 1409] << 8) + RXBUFF[0 * 2 + 12 + 1408])/1000;
}

float MBRead::GetI62()
{
    return (float)((RXBUFF[1 * 2 + 12 + 1409] << 8) + RXBUFF[1 * 2 + 12 + 1408])/1000;
}

float MBRead::GetI81()
{
    return (float)((RXBUFF[2 * 2 + 12 + 1409] << 8) + RXBUFF[2 * 2 + 12 + 1408])/1000;
}

float MBRead::GetI82()
{
    return (float)((RXBUFF[3 * 2 + 12 + 1409] << 8) + RXBUFF[3 * 2 + 12 + 1408])/1000;
}

float MBRead::GetI48()
{
    return (float)((RXBUFF[5 * 2 + 12 + 1409] << 8) + RXBUFF[5 * 2 + 12 + 1408])/100;
}

float MBRead::GetI12()
{
    return (float)((RXBUFF[4 * 2 + 12 + 1409] << 8) + RXBUFF[4 * 2 + 12 + 1408])/1000;
}





#pragma endregion Motor

//Label2.Text = (MB.U(0) / 1000).ToString("F02")              0- 6v1
//        Label5.Text = (MB.U(1) / 1000).ToString("F02")      1 -6v2
//        Label9.Text = (MB.U(2) / 1000).ToString("F02")      2
//        Label13.Text = (MB.U(3) / 1000).ToString("F02")
//        Label17.Text = (MB.U(4) / 1000).ToString("F02")
//        Label21.Text = (MB.U(5) / 100).ToString("F02")
//
//        Label3.Text = (MB.I(o) / 1000).ToString("F02")
//        Label8.Text = (MB.I(1) / 1000).ToString("F02")
//        Label12.Text = (MB.I(2) / 1000).ToString("F02")
//        Label16.Text = (MB.I(3) / 1000).ToString("F02")
//        Label20.Text = (MB.I(4) / 1000).ToString("F02")
//        Label24.Text = (MB.I(5) / 100).ToString("F02")
//ну с 6в1, 6в2, 8в1,8в2, 12в, 48в
