#ifndef CONFIGCONTROLLER_H
#define CONFIGCONTROLLER_H

#include <iostream>
#include <map>
#include "TinyXML/tinyxml.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include "stdlib.h"
#include "Motor.h"
#include "Sensor.h"

using namespace std;

//класс для загрузки и ранения основных параметров приложения
class ConfigController
{
private:
    static ConfigController* mInstance;
    ConfigController();
    ConfigController(ConfigController const&);
    ~ConfigController();

    TiXmlDocument * mXMLConfigFile;

    //настройки двигателей и сенсоров
    std::map<int, Motor> mMotorMap;//Карта двигателей
    std::map<int, Sensor> mSensorMap;//Карта сенсоров

    //накстроки подключения
    std::string mHost;              //адрес назначения
    int mSendPort;                  //порт для записи
    int mReceivePort;               //порт для чтения
    int mSendDelay;                 //интервал записи
    int mReceiveDelay;              //интревал чтения

    //настройки контроллера команд
    int mDefaultStiff;              //Пропорциональный коэффициент по умолчанию
    int mDefaultDump;               //Интегральный коэффициент по умолчанию
    int mDefaultTorque;             //Диффиренциальный коэффициент по умолчанию
    int mDefaultSpeed;              //Скорость перехода в позицию (град за сек)

public:
    static ConfigController* Instance();
    static void Initialize();

    bool OpenFile(std::string FileName);//Открыть файл настроек
    bool SaveFile(std::string FileName);//Сохранить файл настроек

    std::string GetHost();          //получить адрес назначения
    int GetSendPort();              //получить порт записи
    int GetReceivePort();           //получить порт приема
    int GetSendDelay();             //получить интервал записи
    int GetReceiveDelay();          //получить интервал чтения
    void SetHost(std::string host); //задать адрес назначения
    void SetReceivePort(int port);  //задать порт чтения
    void SetSendPort(int port);     //задать порт записи

    std::map<int, Motor> *GetMotorMap();
    std::map<int, Sensor> *GetSensorMap();

    int GetDefaultStiff();
    int GetDefaultDump();
    int GetDefaultTorque();
    int GetDefaultSpeed();
};
#endif // CONFIGCONTROLLER_H
