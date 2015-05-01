#ifndef CHANNELLISTITEM_H
#define CHANNELLISTITEM_H

#include <string>

class ChannelListItem
{
private:

public:
    unsigned int    mNumber;
    std::string     mChannelDesc;
    std::string     mStatus; // TODO: rewrite to enum
    int             mPos;
    int             mMinPos;
    int             mMaxPos;
    bool            mReverce;
    int             mStiff;
    int             mDump;
    int             mTorque;
    int             mCalibration;
    bool            mEnable;
    ChannelListItem();
    ~ChannelListItem();
};

#endif // CHANNELLISTITEM_H
