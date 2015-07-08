#include "Command.h"

Command::Command()
{

}

Command::~Command()
{

}

int Command::GetNumber()
{
    return mNumber;
}

PID Command::GetPID()
{
    return mPID;
}

void Command::SetTime(int Time)
{
    mTime = Time;
}

void Command::SetPosition(int Position)
{
    mPosition = Position;
}

void Command::SetNumber(int Number)
{
    mNumber = Number;
}

void Command::SetPID(PID oPID)
{
    mPID = oPID;
}


int Command::GetTime()
{
    return mTime;
}

int Command::GetPosition()
{
    return mPosition;
}

