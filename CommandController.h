#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#define _USE_MATH_DEFINES

#include "WriteBuffer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include "BufferController.h"
#include "ConfigController.h"
#include <QStateMachine>
#include <QState>
#include <QTime>
#include <QVector>
#include <QDebug>

struct PID
{
    int Stiff = 0;
    int Dump = 0;
    int Torque = 0;
};

struct Command
{
    int Time = 0;
    int Number = 0;
    int Angle = 0;
    PID PIDs;
};

struct MotorPos
{
    double CurrentPos;
    int StartPos;
    int DestPos;
    double Step;
    bool isEndPos;
};

// управление конмандами,
//содержит список команд и по заданному времени обновляет буфер
class CommandController: public QObject
{
    Q_OBJECT
private:
    CommandController();
    ~CommandController(){}
    CommandController(CommandController const&);

    static CommandController* mInst;

    //для выполнения команд из файла
    std::vector<Command> mCommandsList;//список команд
    int mCommandId;
    int mTimeRecord;
    int mCountRows;
    bool IsPlaySequenceState;//состояние выполнения команд из файла

    //для выполнения перехода в заданную позицию
    int mTimeToGo;
    int mDestPos;
    int mStartPos;
    double mCurrentPos;
    int mCurrentTime;
    double mStepPos;
    int mMotorNumber;
    bool IsGoToPosState;//состояние выполнения перехода в позицию за время
    int IsGoToStartPosState;
    int mCurrentTimeForCommands;
    int mSendDelay;
    QTime mTime;
    std::map<int,Motor> * mMotorMap;
    std::map<int,MotorPos> mMotorPosMap;

public:
    static CommandController* Inst(){return mInst;}
    static void Init(){delete mInst; mInst = new CommandController;}

    void Update(long time);
    bool LoadFromFile(std::string fileName);
    int GetCountRows();
    int GetTimeRecord();
    void InitStateMachine();
    bool GetPlaySequenceState();
    void SetPlaySequenceState(bool State);
    void SetCommandId(int cId);
    void NextCommand();
    void SendCommand();
    void SetCurrentTimeForCommands(int Time);
    int GetCurrentPos();

    bool GetGoToPosState();
    void SetGoToPosState(bool State);

    //для перехода в заданный угол (один двигатель)
    void GoNextPos();
    void CalcGoToPos();
    void SetTimeToGo(int TimeToGo);
    void SetDestPos(int DestPos);
    void SetStartPos(int StartPos);
    void SetMotorNumber(int Number);

    //для перехода в начальную позицию (все двигатели)
    void SetPos(int NumberBuffer,int DestPos, int StartPos);
    void GoPos();
    void initPos(bool mode);
    void SetGoToStartPosState(int State);
    void CalcGoToStartPos(long TimeToGo);




signals:
    void initStart();
    void initEnd();
    void PlayEnd();
};



#endif // COMMANDCONTROLLER_H
