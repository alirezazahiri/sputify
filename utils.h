#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "structs.h"
#include "enums.h"


// * HELPERS
std::string join(std::vector<std::string> list, std::string __delim = ",")
{
    std::string res = "";
    size_t size = list.size();
    for (size_t i = 0; i < size; i++)
    {
        res += list[i];
        if (i < size - 1)
            res += __delim;
    }
    return res;
}
std::vector<std::string> split(std::string line, std::string delim)
{
    std::vector<std::string> res;

    size_t start = 0;
    size_t end = line.find(delim);

    while (end != std::string::npos)
    {
        res.push_back(line.substr(start, end - start));
        start = end + delim.length();
        end = line.find(delim, start);
    }

    res.push_back(line.substr(start));

    return res;
}
std::string timeToHHMMSS(Time t, bool __zeroSpan = false)
{
    std::ostringstream ss;
    if (__zeroSpan)
    {
        if (t.hour)
            ss << std::setw(2) << std::setfill('0') << t.hour << ":" << std::setw(2) << std::setfill('0') << t.minute << ":" << std::setw(2) << std::setfill('0') << t.second;
        else
            ss << std::setw(2) << std::setfill('0') << t.minute << ":" << std::setw(2) << std::setfill('0') << t.second;
    }
    else
    {
        if (t.hour)
            ss << t.hour << ":" << std::setw(2) << std::setfill('0') << t.minute << ":" << std::setw(2) << std::setfill('0') << t.second;
        else
            ss << t.minute << ":" << t.second;
    }
    return ss.str();
}
int hhmmssToSeconds(Time t)
{
    return t.hour * 60 * 60 + t.minute * 60 + t.second;
}

Time secondsToHHMMSS(int seconds)
{
    Time result;

    result.hour = seconds / 3600;
    result.minute = (seconds % 3600) / 60;
    result.second = seconds % 60;

    return result;
}

#endif