#include "DriverCommand.h"

DriverCommand::DriverCommand()
{

}

DriverCommand::~DriverCommand()
{

}

int DriverCommand::GetNumber()
{
    return mNumber;
}

PID DriverCommand::GetPID()
{
    return mPID;
}

void DriverCommand::SetTime(int Time)
{
    mTime = Time;
}

void DriverCommand::SetPosition(int Position)
{
    mPosition = Position;
}

void DriverCommand::SetNumber(int Number)
{
    mNumber = Number;
}

void DriverCommand::SetPID(PID oPID)
{
    mPID = oPID;
}


int DriverCommand::GetTime()
{
    return mTime;
}

int DriverCommand::GetPosition()
{
    return mPosition;
}

