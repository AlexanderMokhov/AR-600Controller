#ifndef AR600CONTROLLERCONF_H
#define AR600CONTROLLERCONF_H

#include <iostream>
#include <map>
#include "TinyXML/tinyxml.h"
#include "DriverSettingsItem.h"
#include "MBWrite.h"
#include "MBRead.h"
#include "stdlib.h"
#include "ChannelTableModel.h"

using namespace std;

class AR600ControllerConf
{
private:
    static AR600ControllerConf* mInstance;
    AR600ControllerConf();
    AR600ControllerConf(AR600ControllerConf const&);
    ~AR600ControllerConf();

    TiXmlDocument * mXMLfileSetting;

    std::map<unsigned int,DriverSettingsItem> mDriverSettingsMap;
    int mPort;//порт назначения
    std::string mHost;//адрес назначения
    int mSendDelay;

    int mDefaultStiff;
    int mDefaultDump;
    int mDefaultTorque;

public:
    static AR600ControllerConf* Instance();
    static void Initialize();
    static void Shutdown();

    bool OpenFile(std::string FileName);//открыть файл настроек
    bool SaveFile(std::string FileName);//сохранить файл настроек

    int GetPort();//получить порт
    std::string GetHost();//получить адрес
    int GetSendDelay();//получить интервал отправки

    bool Update(MBWrite *buffer);
    std::map<unsigned int,DriverSettingsItem> *GetConfigMap();
    bool UpdateIlim(MBWrite *bufferWrite,MBRead *bufferRead);

    int GetDefaultStiff();
    int GetDefaultDump();
    int GetDefaultTorque();
};
#endif // AR600CONTROLLERCONF_H
