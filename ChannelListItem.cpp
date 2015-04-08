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
    mKP=900;
    mKI=2;
    mKD=1;
    mIlim=1;
}

ChannelListItem::~ChannelListItem()
{

}

