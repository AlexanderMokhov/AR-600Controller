#include "CommandController.h"

CommandController::CommandController()
{

}

CommandController::~CommandController()
{

}

CommandController::Update(unsigned int mTime, MBWrite &buffer)
{
    if(mCommandsList.at(Id).mTime==mTime)//совпало время
    {
        //читаем все команды с таким временем
        while(mCommandsList.at(Id).mTime==mTime)
        {
            //записываем значение в мотор и проверяем следующую команду
            buffer.MOTOR_ANGLE_set(mCommandsList.at(Id).mChanelNomber,mCommandsList.at(Id).mPosition);
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

        while(std::getline(file, str))
        {
            int i=0;
            while(str[i]==' ')
                i++;
            std::string temp;
            while(str[i]!=' ')
            {
                temp+=str.at(i);
                i++;
            }
            //Получаем номер привода
            unsigned int Number = atoi(temp.c_str());
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
            unsigned int Time = atoi(temp.c_str());
            temp.clear();

            while(str[i]==' ')
                i++;
            while(str[i]!='.')
            {
                temp+=str.at(i);
                i++;
            }
            i++;
            while(str[i]!=' ' && i<str.length())
            {
                temp+=str.at(i);
                i++;
            }
            //Получаем позицию привода
            int Position = atoi(temp.c_str());
            temp.clear();

            //Переводим позицию в градусы*100
            Position=(180.0/M_PI*Position)*100;

            //Заносим полученые параметры в контейнер
            mCommandsList.push_back(DriverCommand(Number,Time,Position));
        }
        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }

}

