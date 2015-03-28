#ifndef AR600CONTOLLERCONF_H
#define AR600CONTOLLERCONF_H

#include<iostream>
#include <vector>
#include "TinyXML/tinyxml.h"
#include "driversettingsitem.h"

using namespace std;

class AR600ContollerConf
{
private:
    static AR600ContollerConf* m_Instance;
    AR600ContollerConf();
    AR600ContollerConf(AR600ContollerConf const&);
    ~AR600ContollerConf();

    TiXmlDocument * XMLfileSetting = NULL;

    std::vector<DriverSettingsItem> m_DriverSettingsVector;
    int m_Port;//порт назначения
    std::string m_Host;//адрес назначения

public:
    static AR600ContollerConf* Instance();
    static void initialize();
    static void shutdown();

    bool openFile(std::string FileName);//открыть файл настроек

    int getPort();//получить порт
    std::string getHost();//получить адрес
};
#endif // AR600CONTOLLERCONF_H
