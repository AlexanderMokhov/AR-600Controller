#ifndef FPACKETDEFINITION_H
#define FPACKETDEFINITION_H

#include <iostream>

#define CHUNNELS 71
#define CHUNNELS_ITEMS 9

const uint16_t FBufferSize  = CHUNNELS * CHUNNELS_ITEMS * sizeof(double);
const uint16_t FChannelsNumber = CHUNNELS;

#endif // FPACKETDEFINITION_H
