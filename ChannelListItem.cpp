#include "ChannelListItem.h"

ChannelListItem::ChannelListItem()
{
    mNumber=0;
    mChannelDesc="Driver";
    mStatus="Disabled"; // TODO: rewrite to enum
    mPos=0;
    mMinPos=-500;
    mMaxPos=500;
    mReverce=false;
    mKI=2;
    mKP=900;
    mKD=1;
    mIlim=1;
}

ChannelListItem::~ChannelListItem()
{

}

