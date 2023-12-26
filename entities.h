#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <string>
#include <vector>

#include "enums.h"
#include "structs.h"

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

#endif