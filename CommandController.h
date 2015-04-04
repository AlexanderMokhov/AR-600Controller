#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#define _USE_MATH_DEFINES

#include "DriverCommand.h"
#include "MBWrite.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>





// управление конмандами,
//содержит список команд и по заданному времени обновляет буфер
class CommandController
{
private:
    std::vector<DriverCommand> mCommandsList;//список команд
    unsigned int Id;
    int TimeRecord;
public:
       CommandController();
    ~CommandController();
       void Update(unsigned int mTime, MBWrite &buffer);
       bool LoadFromFile(std::string fileName);


//       Update (время, буфер) искать в списке команд время и по найденому значению заполнять буфер
//       загрузка списка команд из файла, если файл не праильного формата, сообщать об этом, список команд обнулять
//         сохраниние команд в файл
};

#endif // COMMANDCONTROLLER_H
