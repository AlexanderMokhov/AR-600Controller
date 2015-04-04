#include "CommandController.h"
#include <qdebug.h>

CommandController::CommandController()
{

}

CommandController::~CommandController()
{

}

void CommandController::Update(unsigned int mTime, MBWrite &buffer)
{
    if(mCommandsList.at(Id).getTime()==mTime)//совпало время
    {
        //читаем все команды с таким временем
        while(mCommandsList.at(Id).getTime()==mTime)
        {
            //записываем значение в мотор и проверяем следующую команду
            buffer.MOTOR_ANGLE_set(mCommandsList.at(Id).getNumber(),mCommandsList.at(Id).getPosition());
            Id++;
        }
    }
}

bool CommandController::LoadFromFile(std::string fileName)
{
    std::ifstream file(fileName.c_str());

    if(file.is_open())
    {
        //очищаем список команд
        mCommandsList.clear();
        std::string str;

        int currentTime=0;
        DriverCommand newCommand;
        int lines=0;
        while(std::getline(file, str))
        {
            unsigned int i=0;
            while(str[i]==' ')
                i++;
            std::string temp;
            while(str[i]!=' ')
            {
                temp+=str.at(i);
                i++;
            }
            //Получаем номер привода
            int Number = atoi(temp.c_str());
            temp.clear();

            while(str[i]==' ')
                i++;
            while(str[i]!='.')
            {
                temp+=str.at(i);
                i++;
            }
            i++;
            while(str[i]!=' ')
            {
                temp+=str.at(i);
                i++;
            }
            //Получаем время исполнения
            int Time = atoi(temp.c_str());
            temp.clear();

            while(str[i]==' ')
                i++;
            while(str[i]!=' ' && i<str.length())
            {
                temp+=str.at(i);
                i++;
            }
            //Получаем позицию привода
            double Position = atof(temp.c_str());
            temp.clear();

            //Переводим позицию в градусы*100
            Position=(180.0/M_PI*Position)*100;

            if(Time!=currentTime)
            {
                //следующая команда
                //Заносим полученную команду в список

                mCommandsList.push_back(newCommand);
                newCommand.Clear();
                currentTime = Time;
            }

            newCommand.mTime=Time;
            newCommand.mDriversMap.insert(pair<int,int>(Number,(int)Position));
            lines++;
        }
        //заносим с список команд последнюю команду
        mCommandsList.push_back(newCommand);
        TimeRecord = currentTime;//в микросекундах
        qDebug() << "считано " << QString::number(lines) << " строк" << endl;
        qDebug() << "Время записи " << QString::number((double)TimeRecord/1e6) << " секунд" << endl;

        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }

}

