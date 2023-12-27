#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <string>
#include <vector>

#include "enums.h"
#include "structs.h"
#include "entities.h"
#include "helpers.h"

struct Music
{
    int id;
    std::string name;
    std::string artist;
    int year;
    std::string album;
    std::vector<std::string> tags;
    std::string path;
    Time duration;
};
// void logMusic(Music music, const bool __detail);
// void logAllMusics(std::vector<Music> musics, const bool __detail);

struct PlayList
{
    std::string name;
    std::vector<Music> musics;
    Time duration;
};
// void logPlaylist(PlayList playlist);
// void logAllPlaylists(std::vector<PlayList> playlists);

struct User
{
    int id;
    std::string username;
    std::string password;
    UserStatus status;
    std::vector<PlayList> playlists;
    std::vector<Music> musics;
};
// void logUser(User user, const bool __detail);
// void logAllUsers(std::vector<User> users);

void logUser(User user, const bool __detail)
{
    if (!__detail)
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
                    std::cout << user.playlists[i].name;
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
                    std::cout << user.musics[i].name;
            }
        }
        std::cout << std::endl;
    }
}

void logAllUsers(std::vector<User> users)
{
    std::cout << "ID, Mode, Username, Playlists_number/Songs_number" << std::endl;
    for (size_t i = 0; i < users.size(); i++)
        logUser(users[i], false);
}

void logMusic(Music music, const bool __detail)
{
    std::cout << music.id << ", " << music.name << ", " << music.artist;
    if (__detail)
    {
        std::cout << ", " << music.year << ", " << music.album << ", " << join(music.tags, ";") << ", " << timeToHHMMSSFormat(music.duration);
    }
    std::cout << std::endl;
}

void logAllMusics(std::vector<Music> musics, const bool __detail)
{
    std::cout << "ID, Name, Artist";
    if (__detail)
        std::cout << ", Year, Album, Tags, Duration";
    std::cout << std::endl;
    for (size_t i = 0; i < musics.size(); i++)
        logMusic(musics[i], __detail);
}

void logPlaylist(PlayList playlist)
{
    std::cout << playlist.name << ", " << playlist.musics.size() << ", " << timeToHHMMSSFormat(playlist.duration, true) << std::endl;
}

void logAllPlaylists(std::vector<PlayList> playlists)
{
    std::cout << "Playlist_name, Songs_number, Duration" << std::endl;
    for (size_t i = 0; i < playlists.size(); i++)
        logPlaylist(playlists[i]);
}


#endif