#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>

using namespace std;

//Класс устройств робота
class Device
{
public:
    //public methods
    Device();
    ~Device();
    Device( int number, int channel, std::string name );

    int getNumber();
    int getChannel();
    std::string getName();

    void setNumber( int number );
    void setChannel( int channel );
    void setName( string name );
private:
    //private variable
    int m_number;//номер
    int m_channel;//адрес буфера
    std::string m_name;//название
};

#endif // DEVICE_H
