#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "SettingsStorage.h"
#include "Packets/ARPacketManager.h"

class MotorController
{
public:
    //public methods
    static MotorController* Inst(){return m_inst;}
    static void Initialize(){delete m_inst; m_inst = new MotorController;}


    void stepWork();

    void startZeroing(int motorNumber);
    void stopZeroing();

private:
    //private methods
    MotorController();
    ~MotorController(){}
    MotorController(MotorController const&);

    void startingZeroing();
    void stoppingZeroing();
    void doZeroing();

    //private variable
    static MotorController* m_inst;

    enum StatesToZeroing{START_ZEROING, DO_ZEROING, NOT_WORK, STOP_ZEROING};
    StatesToZeroing m_state;

    int motorNumber;
    int newMotorNumber;
    int waitCount;
};

#endif // MOTORCONTROLLER_H
