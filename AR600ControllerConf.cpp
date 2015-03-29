#include "AR600ControllerConf.h"

AR600ControllerConf * AR600ControllerConf::m_Instance = 0;

AR600ControllerConf::AR600ControllerConf():
	XMLfileSetting(NULL)
{

}

AR600ControllerConf::~AR600ControllerConf()
{

}

void AR600ControllerConf::initialize()
{
    delete m_Instance;
    m_Instance = new AR600ControllerConf;
}

AR600ControllerConf* AR600ControllerConf::Instance()
{
    return m_Instance;
}

void AR600ControllerConf::shutdown()
{
    delete m_Instance;
    m_Instance = 0;
}

bool AR600ControllerConf::openFile(string FileName)
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
        m_DriverSettingsMap.clear();

        // перебор всех двигателей
        while(xml_Driver != NULL)
        {
            //читаем атрибуты
            unsigned int Number = atoi(xml_Driver->FirstChildElement("Number")->GetText());
            unsigned int NumberBuffer = atoi(xml_Driver->FirstChildElement("NumberBuffer")->GetText());
            std::string Name = std::string(xml_Driver->FirstChildElement("Name")->GetText());
            int MinPos = atoi(xml_Driver->FirstChildElement("MinPos")->GetText());
            int MaxPos = atoi(xml_Driver->FirstChildElement("MaxPos")->GetText());
            bool Reverce = strcmp("false",xml_Driver->FirstChildElement("Reverce")->GetText());
            unsigned int STIFF = atoi(xml_Driver->FirstChildElement("Stiff")->GetText());
            unsigned int DUMP = atoi(xml_Driver->FirstChildElement("Dump")->GetText());

            DriverSettingsItem item(Number,NumberBuffer,Name,MinPos,MaxPos,Reverce,STIFF,DUMP);
            //загоняем в контейнер
            m_DriverSettingsMap.insert(pair<unsigned int,DriverSettingsItem>(Number,item));

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

bool AR600ControllerConf::saveFile(string FileName)
{
    TiXmlDocument XMLFile;
    TiXmlDeclaration *decl = new TiXmlDeclaration("1.0","UTF-8","yes");
    XMLFile.LinkEndChild(decl);
    TiXmlElement * xml_root = new TiXmlElement("AR600ControllerConf");
    XMLFile.LinkEndChild(xml_root);
    TiXmlElement * xml_DriverSettings = new TiXmlElement("DriverSettings");
    xml_root->LinkEndChild(xml_DriverSettings);

    TiXmlText * WriteValue;
    char * buffer;
    buffer=(char*)malloc(15*sizeof(char));
    map<unsigned int,DriverSettingsItem>::iterator it;
    //заполняем массив двигателей из контейнера
    for(it = m_DriverSettingsMap.begin();it!=m_DriverSettingsMap.end();++it)
    {
        TiXmlElement * xml_Driver = new TiXmlElement("Driver");
        xml_DriverSettings->LinkEndChild(xml_Driver);

        TiXmlElement* Number = new TiXmlElement("Number");
        WriteValue = new TiXmlText(itoa((*it).second.getNumber(),buffer,10));
        Number->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Number);

        TiXmlElement* NumberBuffer = new TiXmlElement("NumberBuffer");
        WriteValue = new TiXmlText(itoa((*it).second.getNumberBuffer(),buffer,10));
        NumberBuffer->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(NumberBuffer);

        TiXmlElement* Name = new TiXmlElement("Name");
        WriteValue = new TiXmlText((*it).second.getName().c_str());
        Name->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Name);

        TiXmlElement* MinPos = new TiXmlElement("MinPos");
        WriteValue = new TiXmlText(itoa((*it).second.getMinPos(),buffer,10));
        MinPos->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(MinPos);

        TiXmlElement* MaxPos = new TiXmlElement("MaxPos");
        WriteValue = new TiXmlText(itoa((*it).second.getMaxPos(),buffer,10));
        MaxPos->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(MaxPos);

        TiXmlElement* Reverce = new TiXmlElement("Reverce");
        if((*it).second.getReverce()!=0)
            WriteValue = new TiXmlText("true");
        else
            WriteValue = new TiXmlText("false");
        Reverce->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Reverce);

        TiXmlElement* Stiff = new TiXmlElement("Stiff");
        WriteValue = new TiXmlText(itoa((*it).second.getStiff(),buffer,10));
        Stiff->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Stiff);

        TiXmlElement* Dump = new TiXmlElement("Dump");
        WriteValue = new TiXmlText(itoa((*it).second.getDump(),buffer,10));
        Dump->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Dump);
    }

    //записываем настройки подключения
    TiXmlElement * xml_ConnectSettings = new TiXmlElement("ConnectSettings");
    xml_root->LinkEndChild(xml_ConnectSettings);

    TiXmlElement * xml_Host = new TiXmlElement("Host");
    xml_ConnectSettings->LinkEndChild(xml_Host);
    WriteValue=new TiXmlText(m_Host.c_str());
    xml_Host->LinkEndChild(WriteValue);

    TiXmlElement * xml_Port = new TiXmlElement("Port");
    xml_ConnectSettings->LinkEndChild(xml_Port);
    WriteValue=new TiXmlText(itoa(m_Port,buffer,10));
    xml_Port->LinkEndChild(WriteValue);

    //записываем в файл
    XMLFile.SaveFile(FileName.c_str());
    return true;

}

int AR600ControllerConf::getPort()
{
    return m_Port;
}

string AR600ControllerConf::getHost()
{
    return m_Host;
}

// что ты тут хотел возвращать?
bool AR600ControllerConf::Update(MBWrite &buffer)
{
    map<unsigned int,DriverSettingsItem>::iterator it;
    for(it = m_DriverSettingsMap.begin();it!=m_DriverSettingsMap.end();++it)
    {
        buffer.AddressUpdate((*it).first,(*it).second.getNumberBuffer());
        buffer.MOTOR_POS_MIN_set((*it).first,(*it).second.getMinPos());
        buffer.MOTOR_POS_MAX_set((*it).first,(*it).second.getMaxPos());
        buffer.MOTOR_STIFF_set((*it).first,(*it).second.getStiff());
        buffer.MOTOR_DAMP_set((*it).first,(*it).second.getDump());
        if((*it).second.getReverce())
            buffer.MOTOR_SET_REVERS((*it).first);
    }
	return true;
}

