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

struct PosData
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

    QTime mTime;
    std::map<int,Motor> * mMotors;
    std::map<int,PosData> mGoToPosData;

    bool IsPlaySequenceState;//состояние выполнения команд из файла
    bool IsGoToAngleState;//состояние выполнения перехода в позицию за время
    int IsGoToPosState;

    //для выполнения команд из файла
    std::vector<Command> mCommands;
    int mCommandId;
    int mDuration;
    int mCountRows;
    int mCurrentTimeForCommands;
    int mSendDelay;

    //для выполнения перехода в заданный угол
    int mTimeToGo;
    int mDestAngle;
    int mStartAngle;
    double mCurrentAngle;
    double mStep;
    int mMotorNumber;
public:
    static CommandController* Inst(){return mInst;}
    static void Init(){delete mInst; mInst = new CommandController;}

    void DoStepWork();

    //для воспроизведения последовательности команд
    bool OpenFile(std::string fileName);
    void StepPlay(long time);
    int GetCountRows();
    int GetDuration();
    void SetPlaySequenceState(bool State);
    void NextCommand();

    //для перехода в заданный угол (один двигатель)
    void SetupGoToAngle(int MotorNumber, int DestPos, int Time);
    void StartGoToAngle();
    void StepGoToAngle();
    void StopGoToAngle();

    //для перехода в начальную позицию (все двигатели)
    void StartGoToInitialPos(bool mode);
    void SetupGoToInitialPos(long TimeToGo);
    void StepGoToPos();
    void SetPosData(int Number, int DestPos, int StartPos);

signals:
    void InitStart();
    void InitEnd();

    void PlayEnd();
};



#endif // COMMANDCONTROLLER_H
