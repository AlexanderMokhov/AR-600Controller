#ifndef CONFIGCONTROLLER_H
#define CONFIGCONTROLLER_H

#include <iostream>
#include <map>
#include "TinyXML/tinyxml.h"
#include "Driver.h"
#include "MBWrite.h"
#include "MBRead.h"
#include "stdlib.h"
#include "ChannelTableModel.h"
#include "Driver.h"
#include "FootSensor.h"
#include "GyroscopeSensor.h"
#include "Sensor.h"

using namespace std;

class ConfigController
{
private:
    static ConfigController* mInstance;
    ConfigController();
    ConfigController(ConfigController const&);
    ~ConfigController();

    TiXmlDocument * mXMLfileSetting;

    std::map<int, Driver> mDriverMap;
    std::map<int, Sensor> mSensorMap;

    std::string mHost;//адрес назначения
    int mSendPort;//порт назначения
    int mReceivePort;//порт назначения
    int mSendDelay;
    int mReceiveDelay;

    int mDefaultStiff;
    int mDefaultDump;
    int mDefaultTorque;

    int mDefaultSpeed;//градусов за секунду при возвращении в стартовую позицию

public:
    static ConfigController* Instance();
    static void Initialize();
    static void Shutdown();

    bool OpenFile(std::string FileName);//открыть файл настроек
    bool SaveFile(std::string FileName);//сохранить файл настроек

    std::string GetHost();//получить адрес
    int GetSendPort();//получить порт
    int GetReceivePort();//получить порт
    int GetSendDelay();//получить интервал отправки
    void SetHost(std::string host);
    void SetReceivePort(int port);
    void SetSendPort(int port);
    int GetReceiveDelay();//получить интервал обновления

    bool Update(MBWrite *buffer);
    std::map<int, Driver> *GetDriverMap();
    std::map<int, Sensor> *GetSensorMap();

    int GetDefaultStiff();
    int GetDefaultDump();
    int GetDefaultTorque();

    int GetDefaultSpeed();
};
#endif // CONFIGCONTROLLER_H
