#include "DriverCommand.h"

DriverCommand::DriverCommand()
{

}

DriverCommand::DriverCommand(unsigned int Number, unsigned int Time, int Position)
{
    mNumber=Number;
    mTime=Time;
    mPosition=Position;
}

DriverCommand::~DriverCommand()
{

}

unsigned int DriverCommand::getNomber()
{
    return mNumber;
}

unsigned int DriverCommand::getTime()
{
    return mTime;
}

int DriverCommand::getPosition()
{
    return mPosition;
}

