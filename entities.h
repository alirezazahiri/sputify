#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <string>
#include <vector>

#include "enums.h"
#include "structs.h"
#include "utils.h"

struct UserStatus
{
    bool isLoggedIn;
    UserMode mode;
};

struct Music
{
    int id;
    std::string name;
    std::string artist;
    int year;
    std::string album;
    std::vector<std::string> tags;
    Time duration;
};
void logMusic(Music music, bool __detail);
void logAllMusics(std::vector<Music> musics);

struct PlayList
{
    std::string name;
    std::vector<Music> musics;
    Time duration;
};
void logPlaylist(PlayList playlist);
void logAllPlaylists(std::vector<PlayList> playlists);

struct User
{
    int id;
    std::string username;
    std::string password;
    UserStatus status;
    std::vector<PlayList> playlists;
    std::vector<Music> musics;
};
void logUser(User user, bool __detail);
void logAllUsers(std::vector<User> users);

void logUser(User user, bool __detail = false)
{
    if (__detail)
        std::cout << user.id << ", " << (user.status.mode == UserMode::USER ? "user" : "artist") << ", " << user.username << ", " << (user.status.mode == UserMode::USER ? user.playlists.size() : user.musics.size()) << std::endl;
    else
    {
        std::cout << "ID: " << user.id << std::endl;
        std::cout << "Mode: " << (user.status.mode == UserMode::USER ? "user" : "artist") << std::endl;
        std::cout << "Playlists/Songs: ";
        if (user.status.mode == UserMode::USER)
        {
            size_t size = user.playlists.size();
            for (size_t i = 0; i < size; i++)
            {
                if (i < size - 1)
                    std::cout << user.playlists[i].name << ", ";
                if (i < size)
                    std::cout << user.playlists[i].name << std::endl;
            }
        }
        else if (user.status.mode == UserMode::ARTIST)
        {
            size_t size = user.musics.size();
            for (size_t i = 0; i < size; i++)
            {
                if (i < size - 1)
                    std::cout << user.musics[i].name << ", ";
                if (i < size)
                    std::cout << user.musics[i].name << std::endl;
            }
        }
    }
}

void logAllUsers(std::vector<User> users)
{
    std::cout << "ID, Mode, Username, Playlists_number/Songs_number" << std::endl;
    for (size_t i = 0; i < users.size(); i++)
        logUser(users[i]);
}

void logMusic(Music music, bool __detail = false)
{
    std::cout << music.id << ", " << music.name << ", " << music.artist;
    if (__detail)
    {
        std::cout << ", " << music.year << ", " << music.album << ", " << join(music.tags, ";") << ", " << timeToHHMMSS(music.duration);
    }
    std::cout << std::endl;
}
void logAllMusics(std::vector<Music> musics)
{
    std::cout << "ID, Name, Artist" << std::endl;
    for (size_t i = 0; i < musics.size(); i++)
        logMusic(musics[i]);
}

void logPlaylist(PlayList playlist)
{
    std::cout << playlist.name << ", " << playlist.musics.size() << ", " << timeToHHMMSS(playlist.duration, true) << std::endl;
}
void logAllPlaylists(std::vector<PlayList> playlists)
{
    std::cout << "Playlist_name, Songs_number, Duration" << std::endl;
    for (size_t i = 0; i < playlists.size(); i++)
        logPlaylist(playlists[i]);
}

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

int findPlaylistByName(std::vector<PlayList> playlists, std::string name)
{
    for (size_t i = 0; i < playlists.size(); i++)
    {
        if (name == playlists[i].name)
            return i;
    }
    return -1;
}

#endif