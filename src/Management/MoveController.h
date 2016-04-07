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
#include <unistd.h>

#include "Buffers/BufferController.h"
#include "SettingsStorage.h"
#include "MoveCorrector.h"
#include "MovesStorage.h"
#include "RecordController.h"
#include "Connection/FrundTransiver.h"
#include "LogMaster.h"

//!!!
struct Command
{
    int Time = 0;
    int Number = 0;
    int Angle = 0;
    PID PIDs;
};
//!!!
struct PosData
{
    double CurrentPos;
    int StartPos;
    int DestPos;
    double Step;
    bool isEndPos;
};
//!!!
enum States {MovePlay, MovePlayOnline, MoveStarting, MoveStopping,
             GoToAngleStarting, GoToAngle, GoToAngleStopping,
             GoPosStarting, GoToPos, GoToPosEnding, GoPosStopping,
             NotWork};

// управление конмандами,
//содержит список команд и по заданному времени обновляет буфер
class MoveController: public QObject
{
    Q_OBJECT
public:
    //public methods
    static MoveController* Inst(){return m_inst;}
    static void Init(){delete m_inst; m_inst = new MoveController;}

    void doStepWork();

    bool openFile(std::string fileName);
    States getState(){ return m_state; }

    //для воспроизведения последовательности команд
    void stepPlay();
    void startPlay();
    void startingPlay();
    void stopPlay();
    void stoppingPlay();

    // для вопроизведения онлайн
    void stepPlayOnline();
    void startPlayOnline() { m_state = States::MovePlayOnline; }

    //для перехода в заданный угол (один двигатель)
    void stepGoToAngle();
    void startGoToAngle(int Number, int DestAngle, int Time);
    void startingGoToAngle();
    void stopGoToAngle();
    void stoppingGoToAngle();

    //для перехода в начальную позицию (все двигатели)
    void startGoPos(bool isCommand);
    void startingGoPos();
    void setPosData(int Number, int DestPos, int StartPos);
    void setupGoPos(long TimeToGo);
    void stepGoPos();
    void stopGoPos();
    void stoppingGoPos();

    int userStiff = 0;//!!!
    int userDump = 0;//!!!

    bool useUserStiff = false;//!!!
    bool useUserDump = false;//!!!

    void setIsLog(bool value);

signals:
    void InitStart();
    void InitEnd();
    void PlayEnd();

private:
    //private methods
    MoveController();
    ~MoveController(){}
    MoveController(MoveController const&);

    //private variable
    static MoveController* m_inst;
    States m_state; //текущее состояние
    std::mutex m_locker; //мьютекс
    QTime m_time;
    std::map<int,Motor> * m_motors;

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

    bool isLog;

};



#endif // MOVECONTROLLER_H
