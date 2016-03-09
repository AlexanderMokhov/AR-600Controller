#ifndef MOVECONTROLLERFRUND_H
#define MOVECONTROLLERFRUND_H

#include "MovesStorage.h"
#include "Buffers/BufferController.h"
#include "Management/MoveCorrector.h"

class MoveControllerFrund
{

public:
    MoveControllerFrund();
    ~MoveControllerFrund();

    void StepMove();
    void LoadFile(string filename);
};

#endif // MOVECONTROLLERFRUND_H
