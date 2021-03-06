#ifndef SETTINGSSTORAGE_H
#define SETTINGSSTORAGE_H

#include <iostream>
#include <map>
#include "stdlib.h"

#include "Libs/TinyXML/tinyxml.h"
#include "Devices/Motor.h"
#include "Devices/Sensor.h"

using namespace std;
//загрузка и хранение основных параметров приложения
class SettingsStorage
{
public:
    //public methods
    static SettingsStorage* Inst(){ return mInst; }
    static void Init(){ delete mInst; mInst = new SettingsStorage; }

    bool OpenFile( std::string FileName );//Открыть файл настроек
    bool SaveFile( std::string FileName );//Сохранить файл настроек

    std::string GetHost(){ return mHost; }                //получить адрес назначения
    int GetSendPort(){ return mSendPort; }                //получить порт записи
    int GetReceivePort(){ return mReceivePort; }          //получить порт приема
    int GetSendDelay(){ return mSendDelay; }              //получить интервал записи
    int GetReceiveDelay(){ return mReceiveDelay; }        //получить интервал чтения
    void SetHost( std::string host ){ mHost = host; }       //задать адрес назначения
    void SetReceivePort( int port ){ mReceivePort = port; } //задать порт чтения
    void SetSendPort( int port ){ mSendPort = port; }       //задать порт записи

    std::map<int, Motor> *GetMotors(){ return &mMotors; }
    std::map<int, Sensor> *GetSensors(){ return &mSensors; }

    int GetDefaultStiff(){ return mDefaultStiff; }
    int GetDefaultDump(){ return mDefaultDump; }
    int GetDefaultTorque(){ return mDefaultTorque; }
    double GetDefaultStiffFactor(){ return mDefaultStiffFactor; }
    double GetDefaultDumpFactor(){ return mDefaultDumpFactor; }
    double GetDefaultTorqueFactor(){ return mDefaultTorqueFactor; }
    int GetDefaultSpeed(){ return mDefaultSpeed; }

    std::string GetFileForward() { return mFileForward; }
    std::string GetFileBack() { return mFileBack; }

    std::string getModelsPath() { return mModelsPath; }
    std::map<int, std::string> *getFrundModels() { return &mFrundModels; }

private:
    //private variable
    static SettingsStorage* mInst;
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

    double mDefaultStiffFactor;     //Пропорциональный коэффициент по умолчанию (доля)
    double mDefaultDumpFactor;      //Интегральный коэффициент по умолчанию (доля)
    double mDefaultTorqueFactor;    //Диффиренциальный коэффициент по умолчанию (доля)
    int mDefaultSpeed;              //Скорость перехода в позицию (град за сек)

    //настройки файлов стандартных движений
    std::string mFileForward, mFileBack;

    //настройки моделей
    std::string mModelsPath;
    std::map<int, std::string> mFrundModels;   //Карта моделей ФРУНДа

    //private methods
    SettingsStorage();
    SettingsStorage( SettingsStorage const& );
    ~SettingsStorage(){}
};


#endif // SETTINGSSTORAGE_H
