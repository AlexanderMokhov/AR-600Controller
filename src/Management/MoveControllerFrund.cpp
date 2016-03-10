#include "MoveControllerFrund.h"

MoveControllerFrund::MoveControllerFrund()
{

}

MoveControllerFrund::~MoveControllerFrund()
{

}

void MoveControllerFrund::StepMove()
{
    /*MovesStorage::Inst()->LoadFile("DRIVEMAR.TXT");

    int i = 21;

    while(MovesStorage::Inst()->mMoveID < 21)
    {
        //записываем значение в мотор и проверяем следующую команду
        int Number = MovesStorage::Inst()->mMoves[MovesStorage::Inst()->mMoveID].NumberChannel;
        int Angle = MovesStorage::Inst()->mMoves[MovesStorage::Inst()->mMoveID].Angle;

        int Stiff = 0;
        //if(useUserStiff) Stiff = UserStiff;
       Stiff = MovesStorage::Inst()->mMoves[MovesStorage::Inst()->mMoveID].PIDs.Stiff;

        int Dump = 0;
        //if(useUserDump) Dump = UserDump;
        Dump = MovesStorage::Inst()->mMoves[MovesStorage::Inst()->mMoveID].PIDs.Dump;

        int Torque = MovesStorage::Inst()->mMoves[MovesStorage::Inst()->mMoveID].PIDs.Torque;

        BufferController::Inst()->GetBufferS()->SetMotorStiff( Number, Stiff );
        BufferController::Inst()->GetBufferS()->SetMotorDump( Number, Dump );
        BufferController::Inst()->GetBufferS()->SetMotorTorque( Number, Torque );

        int CorrectionValue = MoveCorrector::Inst()->getCorrectValue(Number, MovesStorage::Inst()->mMoves[MovesStorage::Inst()->mMoveID].Time);
        qDebug() << "Корректирующее "  << QString::number(CorrectionValue) << endl;

        BufferController::Inst()->GetBufferS()->SetMotorAngle( Number, Angle + CorrectionValue);
        MovesStorage::Inst()->mMoveID++;
    }*/

}

