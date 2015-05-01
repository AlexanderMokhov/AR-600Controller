#include "ChannelListItem.h"

ChannelListItem::ChannelListItem()
{
    mNumber=0;
    mChannelDesc="Driver";
    mStatus="STOP";
    mPos=0;
    mMinPos=-500;
    mMaxPos=500;
    mReverce=false;
    mStiff=900;
    mDump=2;
    mTorque=1;
    mCalibration=1;
    mEnable=false;
}

ChannelListItem::~ChannelListItem()
{

}

