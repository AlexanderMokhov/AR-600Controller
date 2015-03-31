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
    int             mKI;
    int             mKP;
    int             mKD;
    int             mIlim;
    ChannelListItem();
    ~ChannelListItem();
};

#endif // CHANNELLISTITEM_H
