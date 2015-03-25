#ifndef DRIVERCOMMAND_H
#define DRIVERCOMMAND_H


class DriverCommand
{
private:
    unsigned int mChanelNamber;

    /*
     время
    положение
    кооэффициенты регулятора
    */
public:
    DriverCommand();
    ~DriverCommand();
};

#endif // DRIVERCOMMAND_H
