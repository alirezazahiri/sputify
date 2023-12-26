#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "enums.h"
#include "entities.h"
#include "utils.h"

// * user account commands
void signupCommand(std::string command, std::vector<User> *users, int *currentUser)
{
    if (*currentUser != -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    /*
     * [0]POST [1]signup [2]? [3]username [4]<{username}> [5]password [6]<{password}> [7]mode [8]<mode>
     * size = 9
     * indexes: username = 4, password = 6, mode = 8
     */
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    User user;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    bool isBadRequest = false;

    if (tokens[0] == "POST" && tokens.size() > 8)
    {
        if (tokens[1] == "signup" &&
            tokens[3] == "username" &&
            tokens[5] == "password" &&
            tokens[7] == "mode")
        {
            user.username = tokens[4].substr(1, tokens[4].size() - 2);

            bool usernameExists = checkUsernameExists(*users, user.username);
            if (usernameExists)
                throw(ErrorType::BAD_REQUEST_ERROR);

            user.password = tokens[6].substr(1, tokens[6].size() - 2);

            std::string mode = tokens[8].substr(1, tokens[8].size() - 2);
            if (mode == "user" || mode == "USER")
                user.status.mode = UserMode::USER;
            else if (mode == "artist" || mode == "ARTIST")
                user.status.mode = UserMode::ARTIST;
            else
                isBadRequest = true;

            user.status.isLoggedIn = true;
        }
        else
            isBadRequest = true;
    }
    else
        isBadRequest = true;

    if (isBadRequest)
        throw(ErrorType::BAD_REQUEST_ERROR);

    if (users->empty())
        user.id = 1;
    else
    {
        int lastUserIndex = users->size();
        user.id = (*users)[users->size() - 1].id;
    }

    user.musics = {};
    user.playlists = {};

    *currentUser = users->size();
    users->push_back(user);

    std::cout << "OK" << std::endl;

    return;
}

void loginCommand(std::string command, std::vector<User> *users, int *currentUser)
{
    if (*currentUser != -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    /*
     * [0]POST [1]login [2]? [3]username [4]<{username}> [5]password [6]<{password}>
     * size = 7
     * indexes: username = 4, password = 6
     */
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    bool isBadRequest = false;

    std::string username;
    std::string password;

    if (tokens[0] == "POST" && tokens.size() > 6)
    {
        if (tokens[1] == "login" &&
            tokens[3] == "username" &&
            tokens[5] == "password")
        {
            username = tokens[4].substr(1, tokens[4].size() - 2);
            password = tokens[6].substr(1, tokens[6].size() - 2);
        }
        else
            isBadRequest = true;
    }
    else
        isBadRequest = true;

    if (isBadRequest)
        throw(ErrorType::BAD_REQUEST_ERROR);

    int userIndex = loginUser(*users, username, password);

    if (userIndex == -1)
        throw(ErrorType::NOT_FOUND_ERROR);

    *currentUser = userIndex;

    std::cout << "OK" << std::endl;

    return;
}

void logoutCommand(std::string command, std::vector<User> *users, int *currentUser)
{
    if (*currentUser == -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);

    /*
     * [0]POST [1]logout [2]?
     * size = 2
     * indexes: -
     */
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    bool isBadRequest = false;

    if (tokens[0] == "POST" && tokens.size() > 2)
    {
        if (tokens[1] == "logout")
        {
            (*users)[*currentUser].status.isLoggedIn = false;
            *currentUser = -1;
        }
        else
            isBadRequest = true;
    }
    else
        isBadRequest = true;

    std::cout << "OK" << std::endl;

    return;
}

// * get user/artist musics
void getMusicsCommand(std::string command, std::vector<User> *users, int *currentUser, std::vector<Music> *musics)
{
    if (*currentUser == -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    /*
     * [0]GET [1]musics [2]?
     * size = 3
     * indexes: -
     */

    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    bool isBadRequest = false;

    if (tokens[0] == "GET" && tokens.size() > 2)
    {
        if (tokens[1] != "musics")
            isBadRequest = true;
    }
    else
        isBadRequest = true;

    if (isBadRequest)
        throw ErrorType::BAD_REQUEST_ERROR;

    if (musics->empty())
        throw ErrorType::EMPTY_ERROR;

    logAllMusics(*musics);

    return;
}

void getMusicByIdCommand(std::string command, std::vector<User> *users, int *currentUser, std::vector<Music> *musics)
{
    if (*currentUser == -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    /*
     * [0]GET [1]musics [2]? [3]id [4]<{id}>
     * size = 5
     * indexes: id = 4
     */

    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    bool isBadRequest = false;

    int id;

    if (tokens[0] == "GET" && tokens.size() > 2)
    {
        if (tokens[1] == "musics" && tokens[3] == "id")
        {
            id = stoi(tokens[4].substr(1, tokens[4].size() - 2));
        }
        else
            isBadRequest = true;
    }
    else
        isBadRequest = true;

    if (isBadRequest)
        throw ErrorType::BAD_REQUEST_ERROR;

    int musicIndex = findMusicIndexById(*musics, id);
    if (musicIndex == -1)
        throw ErrorType::NOT_FOUND_ERROR;

    logMusic((*musics)[musicIndex], true);

    return;
}

// * get user/artist profiles
void getAllUsersCommand(std::string command, std::vector<User> *users, int *currentUser)
{
    if (*currentUser == -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    /*
     * [0]GET [1]users [2]?
     * size = 3
     * indexes: -
     */

    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    bool isBadRequest = false;

    if (tokens[0] == "GET" && tokens.size() > 2)
    {
        if (tokens[1] != "users")
            isBadRequest = true;
    }
    else
        isBadRequest = true;

    if (isBadRequest)
        throw ErrorType::BAD_REQUEST_ERROR;

    if (users->empty())
        throw ErrorType::EMPTY_ERROR;

    logAllUsers(*users);

    return;
}

void getUserByIdCommand(std::string command, std::vector<User> *users, int *currentUser)
{
    if (*currentUser == -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    /*
     * [0]GET [1]users [2]? [3]id [4]<{id}>
     * size = 5
     * indexes: id = 4
     */

    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    bool isBadRequest = false;

    int id;

    if (tokens[0] == "GET" && tokens.size() > 2)
    {
        if (tokens[1] == "users" && tokens[3] == "id")
        {
            id = stoi(tokens[4].substr(1, tokens[4].size() - 2));
        }
        else
            isBadRequest = true;
    }
    else
        isBadRequest = true;

    if (isBadRequest)
        throw ErrorType::BAD_REQUEST_ERROR;

    int userIndex = findUserIndexById(*users, id);
    if (userIndex == -1)
        throw ErrorType::NOT_FOUND_ERROR;

    logUser((*users)[userIndex], true);

    return;
}

// * (create new)/(get existing) playlist
void createPlaylistCommand(std::string command, std::vector<User> *users, int *currentUser)
{
    if (*currentUser == -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    if ((*users)[*currentUser].status.mode == UserMode::ARTIST)
        throw ErrorType::BAD_REQUEST_ERROR;
    /*
     * [0]POST [1]playlist [2]? [3]name [4]<{name}>
     * size = 5
     * indexes: name = 4
     */

    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    bool isBadRequest = false;

    std::string playlistName;
    if (tokens[0] == "POST" && tokens.size() > 4)
    {
        if (tokens[1] == "playlist" && tokens[3] == "name")
        {
            playlistName = tokens[4].substr(1, tokens[4].size() - 2);
        }
        else
            isBadRequest = true;
    }
    else
        isBadRequest = true;

    int playlistIndex = findPlaylistByName((*users)[*currentUser].playlists, playlistName);

    if (playlistIndex == -1)
    {
        PlayList playlist = {playlistName, {}, {0, 0, 0}};
        (*users)[*currentUser].playlists.push_back(playlist);
    }
    else
        isBadRequest = true;

    if (isBadRequest)
        throw ErrorType::BAD_REQUEST_ERROR;

    std::cout << "OK" << std::endl;
    return;
}

void getUserPlaylists(std::string command, std::vector<User> *users, int *currentUser)
{
    if (*currentUser == -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    if ((*users)[*currentUser].status.mode == UserMode::ARTIST)
        throw ErrorType::BAD_REQUEST_ERROR;
    /*
     * [0]GET [1]playlist [2]? [3]id [4]<{id}>
     * size = 5
     * indexes: id = 4
     */

    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    bool isBadRequest = false;

    int id;

    if (tokens[0] == "GET" && tokens.size() > 2)
    {
        if (tokens[1] == "playlist" && tokens[3] == "id")
        {
            id = stoi(tokens[4].substr(1, tokens[4].size() - 2));
        }
        else
            isBadRequest = true;
    }
    else
        isBadRequest = true;

    if (isBadRequest)
        throw ErrorType::BAD_REQUEST_ERROR;

    int userIndex = findUserIndexById(*users, id);

    if (userIndex == -1)
        throw(ErrorType::NOT_FOUND_ERROR);

    logAllPlaylists((*users)[userIndex].playlists);

    return;
}

void addMusicToPlaylistCommand(std::string command, std::vector<User> *users, int *currentUser, std::vector<Music> *musics)
{
    if (*currentUser == -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    if ((*users)[*currentUser].status.mode == UserMode::ARTIST)
        throw ErrorType::BAD_REQUEST_ERROR;
    /*
     * [0]PUT [1]add_playlist [2]? [3]name [4]<{name}> [5]id [6]<{id}>
     * size = 7
     * indexes: name = 4, id = 6
     */

    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    bool isBadRequest = false;

    std::string playlistName;
    int id;
    if (tokens[0] == "PUT" && tokens.size() > 4)
    {
        if (tokens[1] == "add_playlist" && tokens[3] == "name" && tokens[5] == "id")
        {
            playlistName = tokens[4].substr(1, tokens[4].size() - 2);
            id = stoi(tokens[6].substr(1, tokens[6].size() - 2));
        }
        else
            isBadRequest = true;
    }
    else
        isBadRequest = true;

    if (isBadRequest)
        throw ErrorType::BAD_REQUEST_ERROR;

    int playlistIndex = findPlaylistByName((*users)[*currentUser].playlists, playlistName);

    if (playlistIndex != -1)
    {
        PlayList playlist = (*users)[*currentUser].playlists[playlistIndex];
        int musicIndex = findMusicIndexById(*musics, id);
        playlist.musics.push_back((*musics)[musicIndex]);
        (*users)[*currentUser].playlists[playlistIndex] = playlist;
    }
    else
        throw ErrorType::NOT_FOUND_ERROR;

    std::cout << "OK" << std::endl;
    return;
}

#endif