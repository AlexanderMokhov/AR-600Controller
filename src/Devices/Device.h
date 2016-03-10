#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>

using namespace std;

//Класс устройств робота
class Device
{
public:
    int m_number;//номер
    int m_channel;//адрес буфера
    std::string m_name;//название

public:
    Device();
    ~Device();
    Device( int number, int channel, std::string name );

    //геттеры
    int getNumber();
    int getChannel();
    std::string getName();

    //сеттеры
    void setNumber( int number );
    void setChannel( int channel );
    void setName( string name );

};

#endif // DEVICE_H
