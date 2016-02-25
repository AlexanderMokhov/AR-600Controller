#ifndef MOVESTORAGE_H
#define MOVESTORAGE_H

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

#include "ConfigController.h"

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
class MoveStorage
{
private:
    MoveStorage();
    ~MoveStorage(){}
    MoveStorage(MoveStorage const&);

    static MoveStorage* mInst;
    std::map<int,Motor> * mMotors;
public:
    std::vector<MoveCommand> mMoves;
    int mMoveID;
    int mDuration;
    int mCountRows;

    int mForwardDuration;
    int mForwardCountRows;
    std::vector<MoveCommand> mForwardMoves;
    int mBackDuration;
    int mBackCountRows;
    std::vector<MoveCommand> mBackMoves;

    void SkipSpace(std::locale loc, std::string str, int *pos);
    void ReadValue(std::string *temp, std::locale loc, int *pos, std::string str);

public:
    static MoveStorage* Inst(){ return mInst; }
    static void Init(){ delete mInst; mInst = new MoveStorage; }

    bool OpenFile(std::string fileName);
    int GetCountRows(){ return mCountRows; }
    int GetDuration(){ return mDuration; }
    std::vector<MoveCommand> * GetMoves(){return &mMoves;}

    bool LoadFile(string filename);
    bool LoadForwardMoves();
    bool LoadBackMoves();
    void setForwardMoves();
    void setBackMoves();
};

#endif // MOVESTORAGE_H
