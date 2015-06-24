#include "ConfigController.h"

ConfigController * ConfigController::mInstance = 0;

ConfigController::ConfigController():
	mXMLfileSetting(NULL)
{

}

ConfigController::~ConfigController()
{

}

void ConfigController::Initialize()
{
    delete mInstance;
    mInstance = new ConfigController;
}

ConfigController* ConfigController::Instance()
{
    return mInstance;
}

void ConfigController::Shutdown()
{
    delete mInstance;
    mInstance = 0;
}

bool ConfigController::OpenFile(string FileName)
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
        TiXmlElement *xml_SensorSettings = 0;
        TiXmlElement *xml_Driver = 0;
        TiXmlElement *xml_FootSensor = 0;
        TiXmlElement *xml_GyroscopeSensor = 0;
        TiXmlElement *xml_Sensor = 0;

        // выбор первого тега после предыдущего (настройки двигателей)
        xml_DriverSettings = xml_root->FirstChildElement("DriverSettings");
        // читаем двигатели
        xml_Driver = xml_DriverSettings->FirstChildElement("Driver");
        // очищаем контейнер
        mDriverSettingsMap.clear();
        mFootSensorMap.clear();

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
            int Calibration = atoi(xml_Driver->FirstChildElement("Calibration")->GetText());
            bool Enable = strcmp("false",xml_Driver->FirstChildElement("Enable")->GetText());

            DriverSettingsItem item(Number,NumberBuffer,Name,MinPos,MaxPos,Reverce,Stiff,Dump,Torque,Calibration,Enable);
            //загоняем в контейнер
            mDriverSettingsMap.insert(pair<unsigned int,DriverSettingsItem>(Number,item));

            xml_Driver = xml_Driver->NextSiblingElement("Driver");
        }

        // выбор первого тега после предыдущего (настройки сенсоров)
        xml_SensorSettings = xml_root->FirstChildElement("SensorSettings");
        // читаем сенсоры стоп
        xml_FootSensor = xml_SensorSettings->FirstChildElement("FootSensor");

        // перебор всех сенсоров стоп
        while(xml_FootSensor != NULL)
        {
            //читаем атрибуты
            unsigned int Number = atoi(xml_FootSensor->FirstChildElement("Number")->GetText());
            unsigned int NumberBuffer = atoi(xml_FootSensor->FirstChildElement("NumberBuffer")->GetText());
            std::string Name = std::string(xml_FootSensor->FirstChildElement("Name")->GetText());
            int Uch0 = atoi(xml_FootSensor->FirstChildElement("Uch0")->GetText());
            int Uch1 = atoi(xml_FootSensor->FirstChildElement("Uch0")->GetText());
            int Uch2 = atoi(xml_FootSensor->FirstChildElement("Uch0")->GetText());
            int Uch3 = atoi(xml_FootSensor->FirstChildElement("Uch0")->GetText());
            FootSensor item(Number,NumberBuffer,Name,Uch0,Uch1,Uch2,Uch3);
            //загоняем в контейнер
            mFootSensorMap.insert(pair<int,FootSensor>(Number,item));
            xml_FootSensor = xml_FootSensor->NextSiblingElement("FootSensor");
        }

        // читаем гироскоп
        xml_GyroscopeSensor = xml_SensorSettings->FirstChildElement("GyroscopeSensor");

        //читаем атрибуты
        unsigned int Number = atoi(xml_GyroscopeSensor->FirstChildElement("Number")->GetText());
        unsigned int NumberBuffer = atoi(xml_GyroscopeSensor->FirstChildElement("NumberBuffer")->GetText());
        std::string Name = std::string(xml_GyroscopeSensor->FirstChildElement("Name")->GetText());

        mGyroscopeSensor = GyroscopeSensor(Number,NumberBuffer,Name);


        // читаем двигатели
        xml_Sensor = xml_SensorSettings->FirstChildElement("Sensor");
        // очищаем контейнер
        mSensorMap.clear();

        // перебор всех сенсоров
        while(xml_Sensor != NULL)
        {
            //читаем атрибуты
            unsigned int Number = atoi(xml_Sensor->FirstChildElement("Number")->GetText());
            unsigned int NumberBuffer = atoi(xml_Sensor->FirstChildElement("NumberBuffer")->GetText());
            std::string Name = std::string(xml_Sensor->FirstChildElement("Name")->GetText());
            int Param = atoi(xml_Sensor->FirstChildElement("Param")->GetText());

            Sensor item = Sensor(Number,NumberBuffer,Name,Param);
            //загоняем в контейнер
            mSensorMap.insert(pair<int,Sensor>(Number,item));

            xml_Sensor = xml_Sensor->NextSiblingElement("Sensor");
        }


        //читаем настройки подключения
        TiXmlElement *xml_ConnectSettings = 0;
        xml_ConnectSettings = xml_root->FirstChildElement("ConnectSettings");

        mHost = std::string(xml_ConnectSettings->FirstChildElement("Host")->GetText());
        mSendPort = atoi(xml_ConnectSettings->FirstChildElement("SendPort")->GetText());
        mReceivePort = atoi(xml_ConnectSettings->FirstChildElement("ReceivePort")->GetText());
        mSendDelay = atoi(xml_ConnectSettings->FirstChildElement("SendDelay")->GetText());

        mReceiveDelay = atoi(xml_ConnectSettings->FirstChildElement("ReceiveDelay")->GetText());

        //читаем настройки контроллера команд
        TiXmlElement *xml_CommandControllerSettings = 0;
        xml_CommandControllerSettings = xml_root->FirstChildElement("CommandControllerSettings");
        mDefaultStiff = atoi(xml_CommandControllerSettings->FirstChildElement("DefaultStiff")->GetText());
        mDefaultDump = atoi(xml_CommandControllerSettings->FirstChildElement("DefaultDump")->GetText());
        mDefaultTorque = atoi(xml_CommandControllerSettings->FirstChildElement("DefaultTorque")->GetText());
        return true;
    }
}

bool ConfigController::SaveFile(string FileName)
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

        TiXmlElement* Calibration = new TiXmlElement("Calibration");
        WriteValue = new TiXmlText(itoa((*it).second.GetCalibration(),buffer,10));
        Calibration->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Calibration);

        TiXmlElement* Enable = new TiXmlElement("Enable");
        if((*it).second.GetEnable()!=0)
            WriteValue = new TiXmlText("true");
        else
            WriteValue = new TiXmlText("false");
        Enable->LinkEndChild(WriteValue);
        xml_Driver->LinkEndChild(Enable);
    }

    //записываем настройки подключения
    TiXmlElement * xml_ConnectSettings = new TiXmlElement("ConnectSettings");
    xml_root->LinkEndChild(xml_ConnectSettings);

    TiXmlElement * xml_Host = new TiXmlElement("Host");
    xml_ConnectSettings->LinkEndChild(xml_Host);
    WriteValue=new TiXmlText(mHost.c_str());
    xml_Host->LinkEndChild(WriteValue);

    TiXmlElement * xml_SendPort = new TiXmlElement("SendPort");
    xml_ConnectSettings->LinkEndChild(xml_SendPort);
    WriteValue=new TiXmlText(itoa(mSendPort,buffer,10));
    xml_SendPort->LinkEndChild(WriteValue);

    TiXmlElement * xml_ReceivePort = new TiXmlElement("ReceivePort");
    xml_ConnectSettings->LinkEndChild(xml_ReceivePort);
    WriteValue=new TiXmlText(itoa(mReceivePort,buffer,10));
    xml_ReceivePort->LinkEndChild(WriteValue);

    TiXmlElement * xml_SendDelay = new TiXmlElement("SendDelay");
    xml_ConnectSettings->LinkEndChild(xml_SendDelay);
    WriteValue=new TiXmlText(itoa(mSendDelay,buffer,10));
    xml_SendDelay->LinkEndChild(WriteValue);

    TiXmlElement * xml_ReceiveDelay = new TiXmlElement("ReceiveDelay");
    xml_ConnectSettings->LinkEndChild(xml_ReceiveDelay);
    WriteValue=new TiXmlText(itoa(mReceiveDelay,buffer,10));
    xml_ReceiveDelay->LinkEndChild(WriteValue);

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

int ConfigController::GetReceivePort()
{
    return mReceivePort;
}

int ConfigController::GetSendPort()
{
    return mSendPort;
}

string ConfigController::GetHost()
{
    return mHost;
}

int ConfigController::GetSendDelay()
{
    return mSendDelay;
}

void ConfigController::SetHost(string host)
{
    mHost = host;
}

void ConfigController::SetReceivePort(int port)
{
    mReceivePort = port;
}

void ConfigController::SetSendPort(int port)
{
    mSendPort = port;
}

int ConfigController::GetReceiveDelay()
{
    return mReceiveDelay;
}

bool ConfigController::Update(MBWrite *buffer)
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
        buffer->Set_MOTOR_TORQUE(NumbBuffer,(*it).second.GetTorque());
        buffer->Set_MOTOR_CALIBRATION(NumbBuffer,(*it).second.GetCalibration());

        buffer->GetReverceMap()->insert(std::pair<int,bool>(NumbBuffer,(*it).second.GetReverce()));
        buffer->GetMinPosMap()->insert(std::pair<int,int>(NumbBuffer,(*it).second.GetMinPos()));
        buffer->GetMaxPosMap()->insert(std::pair<int,int>(NumbBuffer,(*it).second.GetMaxPos()));

        buffer->GetEnableMap()->insert(std::pair<int,bool>(NumbBuffer,(*it).second.GetEnable()));

        buffer->Set_MOTOR_MIN_POS(NumbBuffer,PosMin);
        buffer->Set_MOTOR_MAX_POS(NumbBuffer,PosMax);

        buffer->MOTOR_STOP(NumbBuffer);
    }
    map<int,Sensor>::iterator it2;
    for(it2 = mSensorMap.begin();it2!=mSensorMap.end();++it2)
    {
        int NumbBuffer = (*it2).second.GetNumberBuffer();
        buffer->AddressUpdate(NumbBuffer,NumbBuffer);
    }
    return true;
}

map<unsigned int,DriverSettingsItem> *ConfigController::GetConfigMap()
{
    return &mDriverSettingsMap;
}

std::map<int, Sensor> *ConfigController::GetSensorMap()
{
    return &mSensorMap;
}

int ConfigController::GetDefaultStiff()
{
    return mDefaultStiff;
}

int ConfigController::GetDefaultDump()
{
    return mDefaultDump;
}

int ConfigController::GetDefaultTorque()
{
    return mDefaultTorque;
}


