#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H


// управление конмандами,
//содержит список команд и по заданному времени обновляет буфер
class CommandController
{
public:
       CommandController();
    ~CommandController();

//       Update (время, буфер) искать в списке команд время и по найденому значению заполнять буфер
//       загрузка списка команд из файла, если файл не праильного формата, сообщать об этом, список команд обнулять
//         сохраниние команд в файл
};

#endif // COMMANDCONTROLLER_H
