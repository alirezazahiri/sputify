#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "structs.h"
#include "enums.h"

std::string join(std::vector<std::string> list, const std::string __delim)
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
bool includes(const std::string &input, const std::string &substring)
{
    // Find the substring in the input string
    size_t found = input.find(substring);

    // Check if the substring was found
    return (found != std::string::npos);
}
bool includes(const std::vector<std::string> &items, const std::string &item)
{
    for (size_t i = 0; i < items.size(); i++)
        if (items[i] == item)
            return true;
    return false;
}
template <typename T>
bool removeAtIndex(std::vector<T> &vec, size_t index)
{
    if (index < vec.size())
    {
        vec.erase(vec.begin() + index);
        return true;
    }
    return false;
}
std::vector<std::string> tokenize(const std::string &input)
{
    std::istringstream ss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (ss >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
}
std::string timeToHHMMSSFormat(Time t, const bool __zeroSpan = false)
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
int timeToSeconds(Time t)
{
    return t.hour * 60 * 60 + t.minute * 60 + t.second;
}
Time secondsToTime(int seconds)
{
    Time result;

    result.hour = seconds / 3600;
    result.minute = (seconds % 3600) / 60;
    result.second = seconds % 60;

    return result;
}
Time strToTime(const std::string &timeString)
{
    Time result;

    std::istringstream ss(timeString);
    char delimiter;

    ss >> result.hour >> delimiter >> result.minute >> delimiter >> result.second;

    return result;
}

#endif