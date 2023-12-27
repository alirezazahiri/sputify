#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

#include "enums.h"
#include "entities.h"
#include "utils.h"
#include "helpers.h"

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

    bool isBadRequest = false;

    User user;
    std::map<std::string, std::string> tokenValueMap = parseCommandString(command);

    for (const auto &pair : tokenValueMap)
    {
        if (pair.first == "username")
        {
            user.username = pair.second;
        }
        else if (pair.first == "password")
        {
            user.password = pair.second;
        }
        else if (pair.first == "mode")
        {
            if (pair.second == "user")
                user.status.mode = UserMode::USER;
            else if (pair.second == "artist")
                user.status.mode = UserMode::ARTIST;
            else
            {
                isBadRequest = true;
                break;
            }
        }
        else
        {
            isBadRequest = true;
            break;
        }
    }

    if (isBadRequest)
        throw(ErrorType::BAD_REQUEST_ERROR);

    if (users->empty())
        user.id = 1;
    else
    {
        int lastUserIndex = users->size() - 1;
        user.id = (*users)[lastUserIndex].id + 1;
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

    bool isBadRequest = false;

    std::string username;
    std::string password;

    std::map<std::string, std::string> tokenValueMap = parseCommandString(command);

    for (const auto &pair : tokenValueMap)
    {
        if (pair.first == "username")
        {
            username = pair.second;
        }
        else if (pair.first == "password")
        {
            password = pair.second;
        }
        else
        {
            isBadRequest = true;
            break;
        }
    }

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

    logAllMusics(*musics, false);

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

    bool isBadRequest = false;
    int id;

    std::map<std::string, std::string> tokenValueMap = parseCommandString(command);

    for (const auto &pair : tokenValueMap)
    {
        if (pair.first == "id")
        {
            id = stoi(pair.second);
        }
        else
        {
            isBadRequest = true;
            break;
        }
    }

    if (isBadRequest)
        throw ErrorType::BAD_REQUEST_ERROR;

    int musicIndex = findMusicIndexById(*musics, id);
    if (musicIndex == -1)
        throw ErrorType::NOT_FOUND_ERROR;

    std::cout << "ID, Name, Artist, Year, Album, Tags, Duration" << std::endl;
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

    bool isBadRequest = false;
    int id;

    std::map<std::string, std::string> tokenValueMap = parseCommandString(command);

    for (const auto &pair : tokenValueMap)
    {
        if (pair.first == "id")
        {
            id = stoi(pair.second);
        }
        else
        {
            isBadRequest = true;
            break;
        }
    }

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

    bool isBadRequest = false;
    std::string playlistName;

    std::map<std::string, std::string> tokenValueMap = parseCommandString(command);

    for (const auto &pair : tokenValueMap)
    {
        if (pair.first == "name")
        {
            playlistName = pair.second;
        }
        else
        {
            isBadRequest = true;
            break;
        }
    }

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

void getUserPlaylistsCommand(std::string command, std::vector<User> *users, int *currentUser)
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

    bool isBadRequest = false;
    int id;

    std::map<std::string, std::string> tokenValueMap = parseCommandString(command);

    for (const auto &pair : tokenValueMap)
    {
        if (pair.first == "id")
        {
            id = stoi(pair.second);
        }
        else
        {
            isBadRequest = true;
            break;
        }
    }

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

    bool isBadRequest = false;
    std::string playlistName;
    int id;

    std::map<std::string, std::string> tokenValueMap = parseCommandString(command);

    for (const auto &pair : tokenValueMap)
    {
        if (pair.first == "id")
        {
            id = stoi(pair.second);
        }
        else if (pair.first == "name")
        {
            playlistName = pair.second;
        }
        else
        {
            isBadRequest = true;
            break;
        }
    }

    if (isBadRequest)
        throw ErrorType::BAD_REQUEST_ERROR;

    int playlistIndex = findPlaylistByName((*users)[*currentUser].playlists, playlistName);

    if (playlistIndex != -1)
    {
        PlayList playlist = (*users)[*currentUser].playlists[playlistIndex];
        int musicIndex = findMusicIndexById(*musics, id);
        if (musicIndex == -1)
            throw ErrorType::NOT_FOUND_ERROR;
        playlist.musics.push_back((*musics)[musicIndex]);
        int sum = 0;
        for (const Music m: playlist.musics) {
            sum += timeToSeconds(m.duration);
        }
        playlist.duration = secondsToTime(sum);
        (*users)[*currentUser].playlists[playlistIndex] = playlist;
        
    }
    else
        throw ErrorType::NOT_FOUND_ERROR;

    std::cout << "OK" << std::endl;
    return;
}

// * search music
void searchMusicCommand(std::string command, std::vector<User> *users, int *currentUser, std::vector<Music> *musics)
{
    if (*currentUser == -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    if ((*users)[*currentUser].status.mode == UserMode::ARTIST)
        throw ErrorType::BAD_REQUEST_ERROR;
    /*
     * [0]GET [1]search_music [2]? [3]name [4]<{name}> [5]artist [6]<{artist}> [7]tag [8]<{tag}>
     * size = 7
     * indexes: name = 4, id = 6
     */

    bool isBadRequest = false;
    std::string name = "", artist = "", tag = "";
    std::map<std::string, std::string> tokenValueMap = parseCommandString(command);

    for (const auto &pair : tokenValueMap)
    {
        if (pair.first == "name")
        {
            name = pair.second;
        }
        else if (pair.first == "artist")
        {
            artist = pair.second;
        }
        else if (pair.first == "tag")
        {
            tag = pair.second;
        }
        else
        {
            isBadRequest = true;
            break;
        }
    }

    if (isBadRequest)
        throw ErrorType::BAD_REQUEST_ERROR;

    std::vector<Music> foundMusics = findMusics(*musics, name, artist, tag);

    if (foundMusics.empty())
        throw ErrorType::EMPTY_ERROR;

    logAllMusics(foundMusics, false);

    return;
}

// * share music by artist
void shareMusicCommand(std::string command, std::vector<User> *users, int *currentUser, std::vector<Music> *musics, int *latestMusicID)
{
    if (*currentUser == -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    if ((*users)[*currentUser].status.mode == UserMode::USER)
        throw ErrorType::BAD_REQUEST_ERROR;

    /*
     * [0]POST [1]music [2]? [3]title [4]<{title}> [5]path [6]<{path}> [7]year [8]<{year}> [9]album [10]<{album}> [11]tags [12]<{tags}> [13]duration [14]<{duration}>
     * size = 15
     * indexes: title = 3, path = 5, year = 7, album = 9, tags = 11, duration = 13
     */

    bool isBadRequest = false;
    Music music;

    std::map<std::string, std::string> tokenValueMap = parseCommandString(command);

    for (const auto &pair : tokenValueMap)
    {
        if (pair.first == "title")
        {
            music.name = pair.second;
        }
        else if (pair.first == "path")
        {
            music.path = pair.second;
        }
        else if (pair.first == "year")
        {
            music.year = stoi(pair.second);
        }
        else if (pair.first == "album")
        {
            music.album = pair.second;
        }
        else if (pair.first == "tags")
        {
            music.tags = split(pair.second, ";");
        }
        else if (pair.first == "duration")
        {
            music.duration = strToTime(pair.second);
        }
        else
        {
            isBadRequest = true;
            break;
        }
    }

    *latestMusicID = *latestMusicID + 1;
    music.id = *latestMusicID;

    music.artist = (*users)[*currentUser].username;

    (*users)[*currentUser].musics.push_back(music);
    musics->push_back(music);

    std::cout << "OK" << std::endl;

    return;
}

void deleteMusicCommand(std::string command, std::vector<User> *users, int *currentUser, std::vector<Music> *musics)
{
    if (*currentUser == -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    if ((*users)[*currentUser].status.mode == UserMode::USER)
        throw ErrorType::BAD_REQUEST_ERROR;

    /*
     * [0]DELETE [1]music [2]? [3]id [4]<{id}>
     * size = 5
     * indexes: id = 3
     */

    bool isBadRequest = false;
    int id;

    std::map<std::string, std::string> tokenValueMap = parseCommandString(command);

    for (const auto &pair : tokenValueMap)
    {
        if (pair.first == "id")
        {
            id = stoi(pair.second);
        }
        else
        {
            isBadRequest = true;
            break;
        }
    }

    if (isBadRequest)
        throw ErrorType::BAD_REQUEST_ERROR;

    int publicMusicIndex = findMusicIndexById(*musics, id);

    if (publicMusicIndex == -1)
        throw ErrorType::NOT_FOUND_ERROR;
    if ((*users)[*currentUser].username != (*musics)[publicMusicIndex].artist)
        throw ErrorType::PERMISSION_DENIED_ERROR;

    int artistMusicIndex = findMusicIndexById((*users)[*currentUser].musics, id);

    bool removeFromPublicMusics = removeAtIndex(*musics, publicMusicIndex);
    bool removeFromArtistMusics = removeAtIndex((*users)[*currentUser].musics, artistMusicIndex);

    if (removeFromArtistMusics && removeFromPublicMusics)
        std::cout << "OK" << std::endl;

    return;
}

void showRegisteredMusicsCommand(std::string command, std::vector<User> *users, int *currentUser, std::vector<Music> *musics)
{
    if (*currentUser == -1)
        throw(ErrorType::PERMISSION_DENIED_ERROR);
    if ((*users)[*currentUser].status.mode == UserMode::USER)
        throw ErrorType::BAD_REQUEST_ERROR;

    /*
     * [0]GET [1]registered_musics [2]?
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
        if (tokens[1] != "registered_musics")
            isBadRequest = true;
    }
    else
        isBadRequest = true;

    if (isBadRequest)
        throw ErrorType::BAD_REQUEST_ERROR;
    if ((*users)[*currentUser].musics.empty())
        throw ErrorType::EMPTY_ERROR;

    logAllMusics((*users)[*currentUser].musics, true);

    return;
}

#endif