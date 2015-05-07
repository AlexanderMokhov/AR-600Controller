#ifndef DEVICE_H
#define DEVICE_H

#include "BufferController.h"
#include<iostream>
using namespace std;

//Класс устройств робота
class Device
{
protected:
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

    //сеттеры
    void SetNumber(int Number);
    void SetNumberBuffer(int NumberBuffer);
    void SetName(string Name);

};

#endif // DEVICE_H
