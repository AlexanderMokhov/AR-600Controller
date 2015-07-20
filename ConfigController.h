#ifndef CONFIGCONTROLLER_H
#define CONFIGCONTROLLER_H

#include "TinyXML/tinyxml.h"
#include <iostream>
#include <map>
#include "stdlib.h"
#include "Motor.h"
#include "Sensor.h"

using namespace std;
//загрузка и хранение основных параметров приложения
class ConfigController
{
private:
    static ConfigController* mInst;
    ConfigController();
    ConfigController(ConfigController const&);
    ~ConfigController(){}

    TiXmlDocument * mXMLConfigFile;

    //настройки двигателей и сенсоров
    std::map<int, Motor> mMotors;   //Карта двигателей
    std::map<int, Sensor> mSensors; //Карта сенсоров

    //накстроки подключения
    std::string mHost;              //адрес назначения
    int mSendPort;                  //порт для записи
    int mReceivePort;               //порт для чтения
    int mSendDelay;                 //интервал записи
    int mReceiveDelay;              //интервал чтения

    //настройки контроллера команд
    int mDefaultStiff;              //Пропорциональный коэффициент по умолчанию
    int mDefaultDump;               //Интегральный коэффициент по умолчанию
    int mDefaultTorque;             //Диффиренциальный коэффициент по умолчанию
    int mDefaultSpeed;              //Скорость перехода в позицию (град за сек)

public:
    static ConfigController* Inst(){return mInst;}
    static void Init(){delete mInst; mInst = new ConfigController;}

    bool OpenFile(std::string FileName);//Открыть файл настроек
    bool SaveFile(std::string FileName);//Сохранить файл настроек

    std::string GetHost(){return mHost;}                //получить адрес назначения
    int GetSendPort(){return mSendPort;}                //получить порт записи
    int GetReceivePort(){return mReceivePort;}          //получить порт приема
    int GetSendDelay(){return mSendDelay;}              //получить интервал записи
    int GetReceiveDelay(){return mReceiveDelay;}        //получить интервал чтения
    void SetHost(std::string host){mHost = host;}       //задать адрес назначения
    void SetReceivePort(int port){mReceivePort = port;} //задать порт чтения
    void SetSendPort(int port){mSendPort = port;}       //задать порт записи

    std::map<int, Motor> *GetMotors(){return &mMotors;}
    std::map<int, Sensor> *GetSensors(){return &mSensors;}

    int GetDefaultStiff(){return mDefaultStiff;}
    int GetDefaultDump(){return mDefaultDump;}
    int GetDefaultTorque(){return mDefaultTorque;}
    int GetDefaultSpeed(){return mDefaultSpeed;}
};


#endif // CONFIGCONTROLLER_H
