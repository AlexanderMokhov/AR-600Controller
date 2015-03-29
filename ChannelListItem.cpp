#include "ChannelListItem.h"

ChannelListItem::ChannelListItem()
{
    mNumber=0;
    mChannelDesc="Driver X";
    mStatus="Disabled"; // TODO: rewrite to enum
    mPos=0;
    mMinPos=-500;
    mMaxPos=500;
    mReverce=false;
    mKP=2;
    mKI=1;
    mKD=4;
}

ChannelListItem::~ChannelListItem()
{

}

