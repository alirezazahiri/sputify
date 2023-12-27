#ifndef STRUCTS_H
#define STRUCTS_H

#include "enums.h"

struct Time
{
    int hour;
    int minute;
    int second;
};

struct UserStatus
{
    bool isLoggedIn;
    UserMode mode;
};

#endif