#ifndef DRIVERCOMMAND_H
#define DRIVERCOMMAND_H


class DriverCommand
{
private:
    unsigned int mNumber; //номер канала
    unsigned int mTime; //Время исполнения
    int mPosition; //Позиция мотора
    int mPID; //ПИД кооэффициенты регулятора

public:

    DriverCommand();
    DriverCommand(unsigned int Number, unsigned int Time, int Position);
    ~DriverCommand();

    unsigned int getNumber();
    unsigned int getTime();
    int getPosition();
};

#endif // DRIVERCOMMAND_H
