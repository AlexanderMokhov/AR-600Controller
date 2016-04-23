#ifndef MOVECONTROLLER_H
#define MOVECONTROLLER_H

#define _USE_MATH_DEFINES

#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <mutex>
#include <regex>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "Packets/ARPacketManager.h"
#include "SettingsStorage.h"
#include "MoveCorrector.h"
#include "MovesStorage.h"
#include "RecordController.h"
#include "Connection/FrundTransiver.h"
#include "LogMaster.h"

// управление движением
class MoveController
{
    struct Command
    { int Time = 0; int Number = 0; int Angle = 0; PID PIDs; };

    struct PosData
    { double CurrentPos; int StartPos; int DestPos; double Step;  bool isEndPos; };

public:
    //public methods
    static MoveController* Inst(){return m_inst;}
    static void Initialize(){delete m_inst; m_inst = new MoveController;}

    void doStepWork();

    bool openFile(std::string fileName);
    int getState(){ return m_state; }

    //для воспроизведения последовательности команд
    void startMove();
    void stopMove();

    // для вопроизведения с ФРУНД
    void startMoveFrund() { m_state = States::STEP_MOVE_FRUND; }

    //для перехода в заданный угол (один двигатель)
    void startMotorTransit(int Number, int DestAngle, int Time);
    void stopMotorTransit();

    //для перехода в начальную позицию (все двигатели)
    void startPositionTransit(bool isCommand);
    void stopPositionTransit();

    //public variable

    enum States {STEP_MOVE, STEP_MOVE_FRUND, BEGIN_MOVE, END_MOVE,
                 BEGIN_MOTOR_TRANSIT, STEP_MOTOR_TRANSIT, END_MOTOR_TRANSIT,
                 BEGIN_POSITION_TRANSIT, STEP_POSITION_TRANSIT, END_POSITION_TRANSIT,
                 NOT_WORK};

    int userStiff = 0;//!!!
    int userDump = 0;//!!!

    bool useUserStiff = false;//!!!
    bool useUserDump = false;//!!!

    void setIsLog(bool value);

    void setCurPosAsDefault();

private:
    //private methods
    MoveController();
    ~MoveController(){}
    MoveController(MoveController const&);

    //для воспроизведения последовательности команд
    void stepMove();
    void startingMove();
    void stoppingMove();

    // для вопроизведения онлайн
    void stepMoveFrund();

    //для перехода в заданный угол (один двигатель)
    void stepMotorTransit();
    void startingMotorTransit();
    void stoppingMotorTransit();

    //для перехода в начальную позицию (все двигатели)
    void startingPositionTransit();
    void setPositionData(int Number, int DestPos, int StartPos);
    void setupPositionTransit(long TimeToGo);
    void stepPositionTransit();
    void stoppingPositionTransit();

    //private variable
    static MoveController* m_inst;
    States m_state; //текущее состояние
    std::mutex m_locker; //мьютекс
    std::map<int, Motor> * m_motors;
    std::map<int, int> m_startPosition;

    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

    //для перехода в заданный угол
    int m_timeToTransit, newTimeToTransit;
    int m_destAngle, newDestAngle;
    int m_startAngle, newStartAngle;
    double m_currentAngle;
    double m_stepAngle;
    int m_motorNumber, newMotorNumber;

    //для перехода в начальную позицию
    std::map<int,PosData> m_positionTransitData;
    bool m_positionTransitMode;
    int m_motorExistCount;

    bool isLog;

};



#endif // MOVECONTROLLER_H
