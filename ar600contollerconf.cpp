#include "ar600contollerconf.h"

AR600ContollerConf * AR600ContollerConf::m_Instance = 0;
AR600ContollerConf::AR600ContollerConf()
{

}

AR600ContollerConf::~AR600ContollerConf()
{

}

void AR600ContollerConf::initialize()
{
    delete m_Instance;
    m_Instance = new AR600ContollerConf;
}

AR600ContollerConf* AR600ContollerConf::Instance()
{
    return m_Instance;
}

void AR600ContollerConf::shutdown()
{
    delete m_Instance;
    m_Instance = 0;
}

bool AR600ContollerConf::openFile(string FileName)
{
    XMLfileSetting = new TiXmlDocument(FileName.c_str());

    if(!XMLfileSetting->LoadFile())
    {
        // Файл не был открыт или содежит ошибки | file have any errors
        return false;
    }
    else
    {
        // обработка
        TiXmlElement *xml_root = XMLfileSetting->FirstChildElement();//выбор первого тега
        TiXmlElement *xml_DriverSettings = 0;
        TiXmlElement *xml_Driver = 0;

        // выбор первого тега после предыдущего (настройки двигателей)
        xml_DriverSettings = xml_root->FirstChildElement("DriverSettings");
        // читаем двигатели
        xml_Driver = xml_DriverSettings->FirstChildElement("Driver");
        // очищаем контейнер
        m_DriverSettingsVector.clear();
        int index=0;
        // перебор всех двигателей
        while(xml_Driver != NULL)
        {
            index++;

            //читаем атрибуты
            unsigned int Number = atoi(xml_Driver->FirstChildElement("Number")->GetText());
            unsigned int NumberBuffer = atoi(xml_Driver->FirstChildElement("NumberBuffer")->GetText());
            std::string Name = std::string(xml_Driver->FirstChildElement("Name")->GetText());
            int MinPos = atoi(xml_Driver->FirstChildElement("MinPos")->GetText());
            int MaxPos = atoi(xml_Driver->FirstChildElement("MaxPos")->GetText());
            bool Reverce = strcmp("false",xml_Driver->FirstChildElement("Reverce")->GetText());
            unsigned int STIFF = atoi(xml_Driver->FirstChildElement("Stiff")->GetText());
            unsigned int DUMP = atoi(xml_Driver->FirstChildElement("Dump")->GetText());

            //загоняем в контейнер
            m_DriverSettingsVector.push_back(DriverSettingsItem(
                                                 Number,
                                                 NumberBuffer,
                                                 Name,
                                                 MinPos,
                                                 MaxPos,
                                                 Reverce,
                                                 STIFF,
                                                 DUMP));

            xml_Driver = xml_Driver->NextSiblingElement("Driver");
        }
        //читаем настройки подключения
        TiXmlElement *xml_ConnectSettings = 0;
        xml_ConnectSettings = xml_root->FirstChildElement("ConnectSettings");
        m_Host = std::string(xml_ConnectSettings->FirstChildElement("Host")->GetText());
        m_Port = atoi(xml_ConnectSettings->FirstChildElement("Port")->GetText());
        return true;
    }
}

int AR600ContollerConf::getPort()
{
    return m_Port;
}

string AR600ContollerConf::getHost()
{
    return m_Host;
}

