#include "CommandController.h"

CommandController::CommandController()
{

}

CommandController::~CommandController()
{

}

CommandController::Update(uint mTime, MBWrite &buffer)
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

CommandController::LoadFromFile(QString fileName)
{
    QFile mFile(fileName);
    if(mFile.open(QIODevice::ReadOnly | QIODevice.Text))
    {
        while(!mFile.atEnd())
        {
            //читаем строку
            QString str = mFile.readLine();
            //делим строку на слова, разделенные пробелом
            QStringList lst = str.split(' ');
            //отладочная информация
            QDebug() << lst.at(0) << lst.at(1) << lst.at(2);


        }
    }
    else
    {
        QDebug() << "don't open file";
        //очищаем список команд
        mCommandsList.clear();
    }
}

