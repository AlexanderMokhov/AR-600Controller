#ifndef COMMANDSLISTITEM_H
#define COMMANDSLISTITEM_H

#include <string>


class CommandsListItem
{
public:
    CommandsListItem();
    ~CommandsListItem();

public:
    int             mNumber;
    std::string     mDescription;
    int             mDuration;
    int             mCountRows;
};

#endif // COMMANDSLISTITEM_H
