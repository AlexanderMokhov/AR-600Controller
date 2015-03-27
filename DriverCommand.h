#ifndef DRIVERCOMMAND_H
#define DRIVERCOMMAND_H


class DriverCommand
{
private:
    unsigned int mChanelNomber;
    unsigned int mTime;//Время исполнения
    int mPosition;//Позиция мотора
    int mPID;//ПИД

    /*
     время
    положение
    кооэффициенты регулятора
    */
public:
    DriverCommand();
    DriverCommand(unsigned int ChanelNomber, unsigned int Time, int Position);
    ~DriverCommand();
};

#endif // DRIVERCOMMAND_H
