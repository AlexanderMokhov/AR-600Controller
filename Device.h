#ifndef DEVICE_H
#define DEVICE_H

#include<iostream>
using namespace std;

//Класс устройств робота
class Device
{
private:
    unsigned int    mNumber;//номер
    unsigned int    mNumberBuffer;//адрес буфера
    std::string     mName;//название

public:
    Device();
    ~Device();
    Device(unsigned int Number, unsigned int NumberBuffer, std::string Name);

    //геттеры
    unsigned int GetNumber();
    unsigned int GetNumberBuffer();
    std::string GetName();

};

#endif // DEVICE_H
