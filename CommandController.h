#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include "QFile"
#include "QIODevice"
#include "QList"
#include "DriverCommand.h"
#include "MBWrite.h"
#include "QStringList"
#include "QDebug"


// управление конмандами,
//содержит список команд и по заданному времени обновляет буфер
class CommandController
{
private:
    QList<DriverCommand> mCommandsList;//список команд
    uint Id;
public:
       CommandController();
    ~CommandController();
       Update(uint mTime, MBWrite &buffer);
       LoadFromFile(QString fileName);

//       Update (время, буфер) искать в списке команд время и по найденому значению заполнять буфер
//       загрузка списка команд из файла, если файл не праильного формата, сообщать об этом, список команд обнулять
//         сохраниние команд в файл
};

#endif // COMMANDCONTROLLER_H
