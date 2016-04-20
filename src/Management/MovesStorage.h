#ifndef MOVESSTORAGE_H
#define MOVESSTORAGE_H

#define _USE_MATH_DEFINES

#include <QDebug>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include <mutex>
#include <regex>
#include <unistd.h>

#include "SettingsStorage.h"

struct PID
{
    int Stiff = 0;
    int Dump = 0;
    int Torque = 0;
    double StiffFactor = 0;
    double DumpFactor = 0;
    double TorqueFactor = 0;
};

struct MoveCommand
{
    int Time = 0;
    int NumberChannel = 0;
    int Angle = 0;
    PID PIDs;
};

//для работы с файлами движений
class MovesStorage
{
public:
    //public variable
    std::vector<MoveCommand> m_moves;
    int m_moveID;
    int m_duration;
    int m_rowsNumber;

    int m_forwardDuration;
    int m_forwardRowsNumber;
    std::vector<MoveCommand> m_forwardMoves;
    int m_backDuration;
    int m_backRowsNumber;
    std::vector<MoveCommand> m_backMoves;

    //public methods
    void skipSpace(std::locale loc, const std::string &str, int *pos);
    bool readValue(std::string *temp, std::locale loc, int *pos, const std::string &str, bool isDouble);

    static MovesStorage* Inst(){ return m_inst; }
    static void Initialize(){ delete m_inst; m_inst = new MovesStorage; }

    bool openFile(std::string fileName);
    int getRowsNumber(){ return m_rowsNumber; }
    int getDuration(){ return m_duration; }
    std::vector<MoveCommand> * getMoves(){return &m_moves;}

    bool loadFile(string filename);
    bool loadForwardMoves();
    bool loadBackMoves();
    void setForwardMoves();
    void setBackMoves();

    void resetErrors();
    int getCountErrors();

    void loadDataFromArray(char* array, uint size);
    int getCurrentRow();

    void setStartPosition(int number, int angle);

private:
    //private variable
    static MovesStorage* m_inst;
    std::map<int, Motor> * m_motors;
    std::map<int, int> m_startPosition;
    volatile unsigned int countErrors;
    std::mutex m_locker;

    //private methods
    MovesStorage();
    ~MovesStorage(){}
    MovesStorage(MovesStorage const&);
};

#endif // MOVESSTORAGE_H
