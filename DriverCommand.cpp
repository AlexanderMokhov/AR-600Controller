#include "DriverCommand.h"

DriverCommand::DriverCommand()
{

}

DriverCommand::DriverCommand(unsigned int ChanelNomber, unsigned int Time, int Position)
{
    mChanelNomber=ChanelNomber;
    mTime=Time;
    mPosition=Position;
}

DriverCommand::~DriverCommand()
{

}

