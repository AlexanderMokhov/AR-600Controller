#ifndef DRIVERCOMMAND_H
#define DRIVERCOMMAND_H


class DriverCommand
{
private:


    /*
     время
    положение
    кооэффициенты регулятора
    */
public:
    unsigned int mChanelNomber;
    unsigned int mTime;//Время исполнения
    int mPosition;//Позиция мотора
    int mPID;//ПИД
    DriverCommand();
    DriverCommand(unsigned int ChanelNomber, unsigned int Time, int Position);
    ~DriverCommand();
};

#endif // DRIVERCOMMAND_H
