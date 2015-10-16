#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>

using namespace std;

//Класс устройств робота
class Device
{
public:
    int mNumber;//номер
    int mChannel;//адрес буфера
    std::string mName;//название

public:
    Device();
    ~Device();
    Device(int Number, int Channel, std::string Name);

    //геттеры
    int GetNumber();
    int GetChannel();
    std::string GetName();

    //сеттеры
    void SetNumber(int Number);
    void SetChannel(int Channel);
    void SetName(string Name);

};

#endif // DEVICE_H
