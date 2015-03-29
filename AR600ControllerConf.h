#ifndef AR600CONTROLLERCONF_H
#define AR600CONTROLLERCONF_H

#include<iostream>
#include <vector>
#include "TinyXML/tinyxml.h"
#include "DriverSettingsItem.h"
#include "MBWrite.h"

using namespace std;

class AR600ControllerConf
{
private:
    static AR600ControllerConf* m_Instance;
    AR600ControllerConf();
    AR600ControllerConf(AR600ControllerConf const&);
    ~AR600ControllerConf();

    TiXmlDocument * XMLfileSetting = NULL;

    std::vector<DriverSettingsItem> m_DriverSettingsVector;
    int m_Port;//порт назначения
    std::string m_Host;//адрес назначения

public:
    static AR600ControllerConf* Instance();
    static void initialize();
    static void shutdown();

    bool openFile(std::string FileName);//открыть файл настроек
    bool saveFile(std::string FileName);//сохранить файл настроек

    int getPort();//получить порт
    std::string getHost();//получить адрес

    bool Update(MBWrite &buffer);

};
#endif // AR600CONTROLLERCONF_H
