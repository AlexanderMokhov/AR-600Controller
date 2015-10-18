#ifndef MOVECONTROLLER_H
#define MOVECONTROLLER_H

#define _USE_MATH_DEFINES

#include <QStateMachine>
#include <QState>
#include <QTime>
#include <QVector>
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

#include "Buffers/BufferController.h"
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

enum States {MovePlay, MoveStarting, MoveStopping,
             GoToAngleStarting, GoToAngle, GoToAngleStopping,
             GoPosStarting, GoToPos, GoToPosEnding, GoPosStopping,
             NotWork};

enum OFStates {Succes, Empty, InvalidFormat};

// управление конмандами,
//содержит список команд и по заданному времени обновляет буфер
class MoveController: public QObject
{
    Q_OBJECT
private:
    MoveController();
    ~MoveController(){}
    MoveController(MoveController const&);

    static MoveController* mInst;
    States mState; //текущее состояние
    std::mutex mLocker; //мьютекс
    QTime mTime;
    std::map<int,Motor> * mMotors;

    //для выполнения команд из файла
    std::vector<Command> mCommands;
    int mCommandId;
    int mDuration;
    int mCountRows;
    int mSendDelay;

    //для перехода в заданный угол
    int mTimeToGo, NewTimeToGo;
    int mDestAngle, NewDestAngle;
    int mStartAngle, NewStartAngle;
    double mCurrentAngle;
    double mStep;
    int mMotorNumber, NewMotorNumber;

    //для перехода в начальную позицию
    std::map<int,PosData> mGoToPosData;
    bool mGoPosMode;
    int mMotorExistCount;
    void SkipSpace(std::locale loc, std::string str, unsigned int *i);
    void ReadValue(std::string *temp, std::locale loc, unsigned int *i, std::string str);


public:
    static MoveController* Inst(){return mInst;}
    static void Init(){delete mInst; mInst = new MoveController;}
    OFStates OpenFile(std::string fileName);
    int GetCountRows(){return mCountRows;}
    int GetDuration(){return mDuration;}

    void DoStepWork();
    void NextCommand();//--

    //для воспроизведения последовательности команд
    void StepPlay();
    void StartPlay();
    void StartingPlay();
    void StopPlay();
    void StoppingPlay();

    //для перехода в заданный угол (один двигатель)
    void StepGoToAngle();
    void StartGoToAngle(int Number, int DestAngle, int Time);
    void StartingGoToAngle();
    void StopGoToAngle();
    void StoppingGoToAngle();

    //для перехода в начальную позицию (все двигатели)
    void StartGoPos(bool isCommand);
    void StartingGoPos();
    void SetPosData(int Number, int DestPos, int StartPos);
    void SetupGoPos(long TimeToGo);
    void StepGoToPos();
    void StopGoPos();
    void StoppingGoPos();

signals:
    void InitStart();
    void InitEnd();
    void PlayEnd();
};



#endif // MOVECONTROLLER_H
