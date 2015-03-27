#ifndef DRIVERCOMMAND_H
#define DRIVERCOMMAND_H


class DriverCommand
{
private:
    unsigned int mChanelNomber;
    unsigned int mTime;
    int mPosition;
    int mPID;

    /*
     время
    положение
    кооэффициенты регулятора
    */
public:
    DriverCommand();
    DriverCommand(int ChanelNomber, int Time, int Position)
    ~DriverCommand();
};

#endif // DRIVERCOMMAND_H
