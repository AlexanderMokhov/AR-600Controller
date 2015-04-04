#include "DriverCommand.h"

DriverCommand::DriverCommand()
{
    //mNumber=Number;
    //mTime=Time;
    //mPosition=Position;
    mDriversMap.clear();

}

DriverCommand::~DriverCommand()
{

}

unsigned int DriverCommand::getNumber()
{
    //return mNumber;
}

unsigned int DriverCommand::getTime()
{
    return mTime;
}

int DriverCommand::getPosition()
{
    //return mPosition;
}

void DriverCommand::Clear()
{
    mDriversMap.clear();
}

std::map<int, int> &DriverCommand::GetDriverMap()
{
    return mDriversMap;
}

