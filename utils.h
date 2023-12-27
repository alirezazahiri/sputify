#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>

#include "structs.h"
#include "enums.h"
#include "entities.h"
#include "helpers.h"

// * ENTITY_UTILS
int loginUser(std::vector<User> &users, std::string username, std::string password)
{
    for (size_t i = 0; i < users.size(); ++i)
    {
        if (users[i].username == username)
        {
            if (users[i].password == password)
            {
                users[i].status.isLoggedIn = true;
                return i;
            }
            else
                throw(ErrorType::PERMISSION_DENIED_ERROR);
        }
    }
    return -1;
}
bool checkUsernameExists(std::vector<User> &users, std::string username)
{
    for (size_t i = 0; i < users.size(); ++i)
    {
        if (users[i].username == username)
        {
            return true;
        }
    }
    return false;
}

int findMusicIndexById(std::vector<Music> musics, int id)
{
    for (size_t i = 0; i < musics.size(); i++)
    {
        if (musics[i].id == id)
            return i;
    }
    return -1;
}
int findUserIndexById(std::vector<User> users, int id)
{
    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].id == id)
            return i;
    }
    return -1;
}
int findUserIndexByUsername(std::vector<User> users, std::string username)
{
    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].username == username)
            return i;
    }
    return -1;
}

int findPlaylistByName(std::vector<PlayList> playlists, std::string name)
{
    for (size_t i = 0; i < playlists.size(); i++)
    {
        if (name == playlists[i].name)
            return i;
    }
    return -1;
}

std::vector<Music> findMusics(std::vector<Music> musics, std::string name, std::string artist, std::string tag)
{
    std::vector<Music> eligibleMusics;

    for (size_t i = 0; i < musics.size(); i++)
    {
        bool isOk = true;
        if (!includes(musics[i].name, name))
        {
            isOk = false;
            continue;
        }
        if (!includes(musics[i].artist, artist))
        {
            isOk = false;
            continue;
        }
        if (tag != "")
        {
            if (!includes(musics[i].tags, tag))
            {
                isOk = false;
                continue;
            }
        }
        if (isOk)
            eligibleMusics.push_back(musics[i]);
    }
    return eligibleMusics;
}

int requestVerb(std::string request)
{
    if (request == "GET")
        return Requests::GET;
    else if (request == "POST")
        return Requests::POST;
    else if (request == "PUT")
        return Requests::PUT;
    else if (request == "DELETE")
        return Requests::DELETE;
    return -1;
}

void showErrorMessage(ErrorType errorType)
{
    switch (errorType)
    {
    case ErrorType::BAD_REQUEST_ERROR:
        std::cout << "Bad Request";
        break;
    case ErrorType::NOT_FOUND_ERROR:
        std::cout << "Not Found";
        break;
    case ErrorType::PERMISSION_DENIED_ERROR:
        std::cout << "Permission Denied";
        break;
    case ErrorType::EMPTY_ERROR:
        std::cout << "Empty";
        break;
    default:
        std::cout << "Not Implemented";
        break;
    }
    std::cout << std::endl;
}

std::map<std::string, std::string> parseCommandString(const std::string &commandString)
{
    std::map<std::string, std::string> result;

    std::istringstream iss(commandString);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
        tokens.push_back(token);

    int i = 0;
    std::vector<std::string> keys, values;
    while (i < tokens.size() && tokens[i] != "?")
        i++;
    i++;
    while (i < tokens.size())
    {
        std::string value = "", key = "";
        std::string tk = tokens[i];

        if (tokens[i][0] == '<' && tokens[i][tokens[i].length() - 1] == '>')
        {
            value = tokens[i].substr(1, tokens[i].size() - 2);
        }
        else if (tokens[i][0] == '<')
        {
            std::vector<std::string> tokenSubset;
            while (tokens[i][tokens[i].length() - 1] != '>')
                tokenSubset.push_back(tokens[i++]);
            tokenSubset.push_back(tokens[i]);
            value = join(tokenSubset, " ");
            value = value.substr(1, value.length() - 2);
        }
        else if (tokens[i][0] != '<' && tokens[i][tokens[i].length() - 1] != '>')
        {
            key = tokens[i];
        }

        if (value != "")
            values.push_back(value);
        if (key != "")
            keys.push_back(key);
        i++;
    }

    if (values.size() == keys.size() && values.size() > 0)
    {
        for (size_t i = 0; i < values.size(); i++)
        {
            result[keys[i]] = values[i];
        }
    }
    else
    {
        throw ErrorType::BAD_REQUEST_ERROR;
    }
    return result;
}

#endif