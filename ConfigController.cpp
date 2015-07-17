#include "ConfigController.h"

ConfigController * ConfigController::mInst = 0;

ConfigController::ConfigController()
{
    mXMLConfigFile = NULL;
}

bool ConfigController::OpenFile(string FileName)
{
    mXMLConfigFile = new TiXmlDocument(FileName.c_str());

    if(!mXMLConfigFile->LoadFile())
    {
        //Файл не был открыт или содежит ошибки | file have any errors
        return false;
    }
    else
    {
        //Обработка
        TiXmlElement *xml_root = mXMLConfigFile->FirstChildElement();//выбор первого тега
        TiXmlElement *xml_MotorSettings = 0;
        TiXmlElement *xml_SensorSettings = 0;
        TiXmlElement *xml_Motor = 0;
        TiXmlElement *xml_Sensor = 0;

        //Выбор первого тега после предыдущего (настройки двигателей)
        xml_MotorSettings = xml_root->FirstChildElement("MotorSettings");
        //Читаем двигатели
        xml_Motor = xml_MotorSettings->FirstChildElement("Motor");
        //Очищаем контейнер
        mMotorMap.clear();

        //Перебор всех двигателей
        while(xml_Motor != NULL)
        {
            //Читаем атрибуты
            int Number = atoi(xml_Motor->FirstChildElement("Number")->GetText());
            int NumberBuffer = atoi(xml_Motor->FirstChildElement("NumberBuffer")->GetText());
            std::string Name = std::string(xml_Motor->FirstChildElement("Name")->GetText());
            int MinPos = atoi(xml_Motor->FirstChildElement("MinPos")->GetText());
            int MaxPos = atoi(xml_Motor->FirstChildElement("MaxPos")->GetText());
            bool Reverce = strcmp("false",xml_Motor->FirstChildElement("Reverce")->GetText());
            int Stiff = atoi(xml_Motor->FirstChildElement("Stiff")->GetText());
            int Dump = atoi(xml_Motor->FirstChildElement("Dump")->GetText());
            int Torque = atoi(xml_Motor->FirstChildElement("Torque")->GetText());
            int Calibration = atoi(xml_Motor->FirstChildElement("Calibration")->GetText());
            bool Enable = strcmp("false",xml_Motor->FirstChildElement("Enable")->GetText());

            Motor item(Number,NumberBuffer,Name,MinPos,MaxPos,Reverce,Stiff,Dump,Torque,Calibration,Enable);
            //Добавляем в контейнер
            mMotorMap.insert(pair<int,Motor>(Number,item));

            xml_Motor = xml_Motor->NextSiblingElement("Motor");
        }

        //Выбор первого тега после предыдущего (настройки сенсоров)
        xml_SensorSettings = xml_root->FirstChildElement("SensorSettings");
        //Читаем сенсоры
        xml_Sensor = xml_SensorSettings->FirstChildElement("Sensor");
        //Очищаем контейнер
        mSensorMap.clear();

        //Перебор всех сенсоров
        while(xml_Sensor != NULL)
        {
            //Читаем атрибуты
            int Number = atoi(xml_Sensor->FirstChildElement("Number")->GetText());
            int NumberBuffer = atoi(xml_Sensor->FirstChildElement("NumberBuffer")->GetText());
            std::string Name = std::string(xml_Sensor->FirstChildElement("Name")->GetText());
            std::string NameLog = std::string(xml_Sensor->FirstChildElement("NameLog")->GetText());
            int Param = atoi(xml_Sensor->FirstChildElement("Param")->GetText());

            Sensor item = Sensor(Number,NumberBuffer,Name,NameLog,Param);
            //Добавляем в контейнер
            mSensorMap.insert(pair<int,Sensor>(Number,item));

            xml_Sensor = xml_Sensor->NextSiblingElement("Sensor");
        }


        //Читаем настройки подключения
        TiXmlElement *xml_ConnectSettings = 0;
        xml_ConnectSettings = xml_root->FirstChildElement("ConnectSettings");

        mHost = std::string(xml_ConnectSettings->FirstChildElement("Host")->GetText());
        mSendPort = atoi(xml_ConnectSettings->FirstChildElement("SendPort")->GetText());
        mReceivePort = atoi(xml_ConnectSettings->FirstChildElement("ReceivePort")->GetText());
        mSendDelay = atoi(xml_ConnectSettings->FirstChildElement("SendDelay")->GetText());
        mReceiveDelay = atoi(xml_ConnectSettings->FirstChildElement("ReceiveDelay")->GetText());

        //Читаем настройки контроллера команд
        TiXmlElement *xml_CommandControllerSettings = 0;
        xml_CommandControllerSettings = xml_root->FirstChildElement("CommandControllerSettings");
        mDefaultStiff = atoi(xml_CommandControllerSettings->FirstChildElement("DefaultStiff")->GetText());
        mDefaultDump = atoi(xml_CommandControllerSettings->FirstChildElement("DefaultDump")->GetText());
        mDefaultTorque = atoi(xml_CommandControllerSettings->FirstChildElement("DefaultTorque")->GetText());
        mDefaultSpeed = atoi(xml_CommandControllerSettings->FirstChildElement("DefaultSpeed")->GetText());

        return true;
    }
}

bool ConfigController::SaveFile(string FileName)
{
    mXMLConfigFile = new TiXmlDocument();
    TiXmlDeclaration *decl = new TiXmlDeclaration("1.0","ANSI","yes");
    mXMLConfigFile->LinkEndChild(decl);
    TiXmlElement * xml_root = new TiXmlElement("AR600ControllerConf");
    mXMLConfigFile->LinkEndChild(xml_root);
    TiXmlElement * xml_MotorSettings = new TiXmlElement("MotorSettings");
    xml_root->LinkEndChild(xml_MotorSettings);

    TiXmlText * WriteValue;
    char * buffer;
    buffer=(char*)malloc(20*sizeof(char));

    //Заполняем массив двигателей из контейнера
    for(auto it = mMotorMap.begin();it!=mMotorMap.end();++it)
    {
        TiXmlElement * xml_Motor = new TiXmlElement("Motor");
        xml_MotorSettings->LinkEndChild(xml_Motor);

        TiXmlElement* Number = new TiXmlElement("Number");
        WriteValue = new TiXmlText(itoa((*it).second.GetNumber(),buffer,10));
        Number->LinkEndChild(WriteValue);
        xml_Motor->LinkEndChild(Number);

        TiXmlElement* NumberBuffer = new TiXmlElement("NumberBuffer");
        WriteValue = new TiXmlText(itoa((*it).second.GetNumberBuffer(),buffer,10));
        NumberBuffer->LinkEndChild(WriteValue);
        xml_Motor->LinkEndChild(NumberBuffer);

        TiXmlElement* Name = new TiXmlElement("Name");
        WriteValue = new TiXmlText((*it).second.GetName().c_str());
        Name->LinkEndChild(WriteValue);
        xml_Motor->LinkEndChild(Name);

        TiXmlElement* MinPos = new TiXmlElement("MinPos");
        WriteValue = new TiXmlText(itoa((*it).second.GetMinPos(),buffer,10));
        MinPos->LinkEndChild(WriteValue);
        xml_Motor->LinkEndChild(MinPos);

        TiXmlElement* MaxPos = new TiXmlElement("MaxPos");
        WriteValue = new TiXmlText(itoa((*it).second.GetMaxPos(),buffer,10));
        MaxPos->LinkEndChild(WriteValue);
        xml_Motor->LinkEndChild(MaxPos);

        TiXmlElement* Reverce = new TiXmlElement("Reverce");
        if((*it).second.GetReverce()!=0)
            WriteValue = new TiXmlText("true");
        else
            WriteValue = new TiXmlText("false");
        Reverce->LinkEndChild(WriteValue);
        xml_Motor->LinkEndChild(Reverce);

        TiXmlElement* Stiff = new TiXmlElement("Stiff");
        WriteValue = new TiXmlText(itoa((*it).second.GetStiff(),buffer,10));
        Stiff->LinkEndChild(WriteValue);
        xml_Motor->LinkEndChild(Stiff);

        TiXmlElement* Dump = new TiXmlElement("Dump");
        WriteValue = new TiXmlText(itoa((*it).second.GetDump(),buffer,10));
        Dump->LinkEndChild(WriteValue);
        xml_Motor->LinkEndChild(Dump);

        TiXmlElement* Torque = new TiXmlElement("Torque");
        WriteValue = new TiXmlText(itoa((*it).second.GetTorque(),buffer,10));
        Torque->LinkEndChild(WriteValue);
        xml_Motor->LinkEndChild(Torque);

        TiXmlElement* Calibration = new TiXmlElement("Calibration");
        WriteValue = new TiXmlText(itoa((*it).second.GetCalibration(),buffer,10));
        Calibration->LinkEndChild(WriteValue);
        xml_Motor->LinkEndChild(Calibration);

        TiXmlElement* Enable = new TiXmlElement("Enable");
        if((*it).second.GetEnable()!=0)
            WriteValue = new TiXmlText("true");
        else
            WriteValue = new TiXmlText("false");
        Enable->LinkEndChild(WriteValue);
        xml_Motor->LinkEndChild(Enable);
    }

    TiXmlElement * xml_SensorSettings = new TiXmlElement("SensorSettings");
    xml_root->LinkEndChild(xml_SensorSettings);

    buffer=(char*)malloc(20*sizeof(char));
    //заполняем массив двигателей из контейнера
    for(auto it2 = mSensorMap.begin();it2!=mSensorMap.end();++it2)
    {
        TiXmlElement * xml_Sensor = new TiXmlElement("Sensor");
        xml_SensorSettings->LinkEndChild(xml_Sensor);

        TiXmlElement* Number = new TiXmlElement("Number");
        WriteValue = new TiXmlText(itoa((*it2).second.GetNumber(),buffer,10));
        Number->LinkEndChild(WriteValue);
        xml_Sensor->LinkEndChild(Number);

        TiXmlElement* NumberBuffer = new TiXmlElement("NumberBuffer");
        WriteValue = new TiXmlText(itoa((*it2).second.GetNumberBuffer(),buffer,10));
        NumberBuffer->LinkEndChild(WriteValue);
        xml_Sensor->LinkEndChild(NumberBuffer);

        TiXmlElement* Name = new TiXmlElement("Name");
        WriteValue = new TiXmlText((*it2).second.GetName().c_str());
        Name->LinkEndChild(WriteValue);
        xml_Sensor->LinkEndChild(Name);

        TiXmlElement* NameLog = new TiXmlElement("NameLog");
        WriteValue = new TiXmlText((*it2).second.GetNameLog().c_str());
        NameLog->LinkEndChild(WriteValue);
        xml_Sensor->LinkEndChild(NameLog);

        TiXmlElement* Param = new TiXmlElement("Param");
        WriteValue = new TiXmlText(itoa((*it2).second.GetParam(),buffer,10));
        Param->LinkEndChild(WriteValue);
        xml_Sensor->LinkEndChild(Param);
    }

    //Записываем настройки подключения
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

    //Записываем настройки контроллера команд
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

    TiXmlElement * xml_DefaultSpeed = new TiXmlElement("DefaultSpeed");
    xml_CommandControllerSettings->LinkEndChild(xml_DefaultSpeed);
    WriteValue=new TiXmlText(itoa(mDefaultSpeed,buffer,10));
    xml_DefaultSpeed->LinkEndChild(WriteValue);

    //Сохраняем файл
    mXMLConfigFile->SaveFile(FileName.c_str());
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

std::map<int,Motor> *ConfigController::GetMotorMap()
{
    return &mMotorMap;
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

int ConfigController::GetDefaultSpeed()
{
    return mDefaultSpeed;
}


