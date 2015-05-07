#ifndef CONFIGCONTROLLER_H
#define CONFIGCONTROLLER_H

#include <iostream>
#include <map>
#include "TinyXML/tinyxml.h"
#include "DriverSettingsItem.h"
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

    std::map<unsigned int,DriverSettingsItem> mDriverSettingsMap;
    std::map<int, FootSensor> mFootSensorMap;
    GyroscopeSensor mGyroscopeSensor;

    std::map<int, Sensor> mSensorMap;

    std::string mHost;//адрес назначения
    int mSendPort;//порт назначения
    int mReceivePort;//порт назначения
    int mSendDelay;
    int mReceiveDelay;

    int mDefaultStiff;
    int mDefaultDump;
    int mDefaultTorque;

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
    std::map<unsigned int,DriverSettingsItem> *GetConfigMap();
    std::map<int, Sensor> *GetSensorMap();
    bool UpdateCalibration(MBWrite *bufferWrite,MBRead *bufferRead);

    int GetDefaultStiff();
    int GetDefaultDump();
    int GetDefaultTorque();
};
#endif // CONFIGCONTROLLER_H
