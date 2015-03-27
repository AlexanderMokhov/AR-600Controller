#include "CommandController.h"

CommandController::CommandController()
{

}

CommandController::~CommandController()
{

}

CommandController::Update(uint mTime, MBWrite &buffer)
{
    if(mCommandsList.at(Id).mTime==mTime)//совпало время
    {
        //читаем все команды с таким временем
        while(mCommandsList.at(Id).mTime==mTime)
        {
            //записываем значение в мотор и проверяем следующую команду
            buffer.MOTOR_ANGLE_set(mCommandsList.at(Id).mChanelNomber,mCommandsList.at(Id).mPosition);
            Id++;
        }
    }
}

