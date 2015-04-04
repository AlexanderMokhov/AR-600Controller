#include "AR600ControllerConf.h"

AR600ControllerConf * AR600ControllerConf::mInstance = 0;

AR600ControllerConf::AR600ControllerConf():
	mXMLfileSetting(NULL)
{

}

AR600ControllerConf::~AR600ControllerConf()
{

}

void AR600ControllerConf::Initialize()
{
    delete mInstance;
    mInstance = new AR600ControllerConf;
}

AR600ControllerConf* AR600ControllerConf::Instance()
{
    return mInstance;
}

void AR600ControllerConf::Shutdown()
{
    delete mInstance;
    mInstance = 0;
}

bool AR600ControllerConf::OpenFile(string FileName)
{
    mXMLfileSetting = new TiXmlDocument(FileName.c_str());

    if(!mXMLfileSetting->LoadFile())
    {
        // Файл не был открыт или содежит ошибки | file have any errors
        return false;
    }
    else
    {
        // обработка
        TiXmlElement *xml_root = mXMLfileSetting->FirstChildElement();//выбор первого тега
        TiXmlElement *xml_DriverSettings = 0;
        TiXmlElement *xml_Driver = 0;

        // выбор первого тега после предыдущего (настройки двигателей)
        xml_DriverSettings = xml_root->FirstChildElement("DriverSettings");
        // читаем двигатели
        xml_Driver = xml_DriverSettings->FirstChildElement("Driver");
        // очищаем контейнер
        mDriverSettingsMap.clear();

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
            int Stiff = atoi(xml_Driver->FirstChildElement("Stiff")->GetText());
            int Dump = atoi(xml_Driver->FirstChildElement("Dump")->GetText());
            int Torque = atoi(xml_Driver->FirstChildElement("Torque")->GetText());
            int Ilim = atoi(xml_Driver->FirstChildElement("Ilim")->GetText());

            DriverSettingsItem item(Number,NumberBuffer,Name,MinPos,MaxPos,Reverce,Stiff,Dump,Torque,Ilim);
            //загоняем в контейнер
            mDriverSettingsMap.insert(pair<unsigned int,DriverSettingsItem>(Number,item));

            xml_Driver = xml_Driver->NextSiblingElement("Driver");
        }

        //читаем настройки подключения
        TiXmlElement *xml_ConnectSettings = 0;
        xml_ConnectSettings = xml_root->FirstChildElement("ConnectSettings");
        mHost = std::string(xml_ConnectSettings->FirstChildElement("Host")->GetText());
        mPort = atoi(xml_ConnectSettings->FirstChildElement("Port")->GetText());

        //читаем настройки контроллера команд
        TiXmlElement *xml_CommandControllerSettings = 0;
        xml_CommandControllerSettings = xml_root->FirstChildElement("CommandControllerSettings");
        mDefaultStiff = atoi(xml_CommandControllerSettings->FirstChildElement("DefaultStiff")->GetText());
        mDefaultDump = atoi(xml_CommandControllerSettings->FirstChildElement("DefaultDump")->GetText());
        mDefaultTorque = atoi(xml_CommandControllerSettings->FirstChildElement("DefaultTorque")->GetText());
        return true;
    }
}

bool AR600ControllerConf::SaveFile(string FileName)
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
    for(it = mDriverSettingsMap.begin();it!=mDriverSettingsMap.end();++it)
    {
        TiXmlElement * xml_Driver = new TiXmlElement("Driver");
        xml_DriverSettings->LinkEndChild(xml_Driver);

        TiXmlElement* Number = new TiXmlElement("Number");
        WriteValue = new TiXmlText(itoa((*it).second.GetNumber(),buffer,10));
        Number->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Number);

        TiXmlElement* NumberBuffer = new TiXmlElement("NumberBuffer");
        WriteValue = new TiXmlText(itoa((*it).second.GetNumberBuffer(),buffer,10));
        NumberBuffer->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(NumberBuffer);

        TiXmlElement* Name = new TiXmlElement("Name");
        WriteValue = new TiXmlText((*it).second.GetName().c_str());
        Name->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Name);

        TiXmlElement* MinPos = new TiXmlElement("MinPos");
        WriteValue = new TiXmlText(itoa((*it).second.GetMinPos(),buffer,10));
        MinPos->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(MinPos);

        TiXmlElement* MaxPos = new TiXmlElement("MaxPos");
        WriteValue = new TiXmlText(itoa((*it).second.GetMaxPos(),buffer,10));
        MaxPos->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(MaxPos);

        TiXmlElement* Reverce = new TiXmlElement("Reverce");
        if((*it).second.GetReverce()!=0)
            WriteValue = new TiXmlText("true");
        else
            WriteValue = new TiXmlText("false");
        Reverce->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Reverce);

        TiXmlElement* Stiff = new TiXmlElement("Stiff");
        WriteValue = new TiXmlText(itoa((*it).second.GetStiff(),buffer,10));
        Stiff->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Stiff);

        TiXmlElement* Dump = new TiXmlElement("Dump");
        WriteValue = new TiXmlText(itoa((*it).second.GetDump(),buffer,10));
        Dump->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Dump);

        TiXmlElement* Torque = new TiXmlElement("Torque");
        WriteValue = new TiXmlText(itoa((*it).second.GetTorque(),buffer,10));
        Torque->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Torque);

        TiXmlElement* Ilim = new TiXmlElement("Ilim");
        WriteValue = new TiXmlText(itoa((*it).second.GetIlim(),buffer,10));
        Ilim->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Ilim);
    }

    //записываем настройки подключения
    TiXmlElement * xml_ConnectSettings = new TiXmlElement("ConnectSettings");
    xml_root->LinkEndChild(xml_ConnectSettings);

    TiXmlElement * xml_Host = new TiXmlElement("Host");
    xml_ConnectSettings->LinkEndChild(xml_Host);
    WriteValue=new TiXmlText(mHost.c_str());
    xml_Host->LinkEndChild(WriteValue);

    TiXmlElement * xml_Port = new TiXmlElement("Port");
    xml_ConnectSettings->LinkEndChild(xml_Port);
    WriteValue=new TiXmlText(itoa(mPort,buffer,10));
    xml_Port->LinkEndChild(WriteValue);

    //записываем настройки контроллера команд
    TiXmlElement * xml_CommandControllerSettings = new TiXmlElement("CommandControllerSettings");
    xml_root->LinkEndChild(xml_CommandControllerSettings);

    TiXmlElement * xml_DefaultStiff = new TiXmlElement("DefaultStiff");
    xml_CommandControllerSettings->LinkEndChild(xml_DefaultStiff);
    WriteValue=new TiXmlText(itoa(mDefaultStiff,buffer,10));
    xml_DefaultStiff->LinkEndChild(WriteValue);

    TiXmlElement * xml_DefaultDump = new TiXmlElement("DefaultDump");
    xml_CommandControllerSettings->LinkEndChild(xml_DefaultDump);
    WriteValue=new TiXmlText(itoa(mDefaultDump,buffer,10));
    xml_DefaultDump->LinkEndChild(WriteValue);

    TiXmlElement * xml_DefaultTorque = new TiXmlElement("DefaultTorque");
    xml_CommandControllerSettings->LinkEndChild(xml_DefaultTorque);
    WriteValue=new TiXmlText(itoa(mDefaultTorque,buffer,10));
    xml_DefaultTorque->LinkEndChild(WriteValue);

    //записываем в файл
    XMLFile.SaveFile(FileName.c_str());
    return true;

}

int AR600ControllerConf::getPort()
{
    return mPort;
}

string AR600ControllerConf::getHost()
{
    return mHost;
}

// что ты тут хотел возвращать?
bool AR600ControllerConf::Update(MBWrite *buffer)
{
    map<unsigned int,DriverSettingsItem>::iterator it;
    for(it = mDriverSettingsMap.begin();it!=mDriverSettingsMap.end();++it)
    {
        int NumbBuffer = (*it).second.GetNumberBuffer();
        buffer->AddressUpdate(NumbBuffer,(*it).first);
        int PosMin = (*it).second.GetMinPos();
        int PosMax = (*it).second.GetMaxPos();

        buffer->MOTOR_STOP(NumbBuffer);

        buffer->Set_MOTOR_STIFF(NumbBuffer,(*it).second.GetStiff());
        buffer->Set_MOTOR_DAMP(NumbBuffer,(*it).second.GetDump());
        buffer->Set_MOTOR_ILIM(NumbBuffer,(*it).second.GetIlim());

        buffer->GetReverceMap().insert(std::pair<int,bool>(NumbBuffer,(*it).second.GetReverce()));

        buffer->Set_MOTOR_MIN_POS(NumbBuffer,PosMin);
        buffer->Set_MOTOR_MAX_POS(NumbBuffer,PosMax);

        buffer->MOTOR_STOP(NumbBuffer);
    }
    return true;
}

map<unsigned int,DriverSettingsItem> *AR600ControllerConf::GetConfigMap()
{
    return &mDriverSettingsMap;
}

bool AR600ControllerConf::UpdateIlim(MBWrite *bufferWrite, MBRead *bufferRead)
{
   // map<unsigned int,DriverSettingsItem>::iterator it;
   // for(it = m_DriverSettingsMap.begin();it!=m_DriverSettingsMap.end();++it)
   // {
    //    bufferRead->MOTOR_POS_MIN_set((*it).first,(*it).second.getMinPos());
    //    bufferRead->MOTOR_POS_MAX_set((*it).first,(*it).second.getMaxPos());
    //    bufferRead->MOTOR_STIFF_set((*it).first,(*it).second.getStiff());
    //    bufferRead->MOTOR_DAMP_set((*it).first,(*it).second.getDump());
    //    if((*it).second.getReverce())
     //       bufferRead->MOTOR_SET_REVERS((*it).first);
    //    bufferRead->MOTOR_ILIM_set((*it).first,bufferRead->MOTOR_CPOS_get((*it).first));
    //}
    //return true;
    return false;
}

int AR600ControllerConf::GetDefaultStiff()
{
    return mDefaultStiff;
}

int AR600ControllerConf::GetDefaultDump()
{
    return mDefaultDump;
}

int AR600ControllerConf::GetDefaultTorque()
{
    return mDefaultTorque;
}


