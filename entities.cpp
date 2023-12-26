#include <iostream>
#include <string>
#include <vector>

#include "enums.h"
#include "structs.h"
#include "entities.h"
#include "helpers.h"

using namespace std;

void logUser(User user, bool __detail = false)
{
    if (__detail)
        cout << user.id << ", " << (user.status.mode == UserMode::USER ? "user" : "artist") << ", " << user.username << ", " << (user.status.mode == UserMode::USER ? user.playlists.size() : user.musics.size()) << endl;
    else
    {
        cout << "ID: " << user.id << endl;
        cout << "Mode: " << (user.status.mode == UserMode::USER ? "user" : "artist") << endl;
        cout << "Playlists/Songs: ";
        if (user.status.mode == UserMode::USER)
        {
            size_t size = user.playlists.size();
            for (size_t i = 0; i < size; i++)
            {
                if (i < size - 1)
                    cout << user.playlists[i].name << ", ";
                if (i < size)
                    cout << user.playlists[i].name;
            }
        }
        else if (user.status.mode == UserMode::ARTIST)
        {
            size_t size = user.musics.size();
            for (size_t i = 0; i < size; i++)
            {
                if (i < size - 1)
                    cout << user.musics[i].name << ", ";
                if (i < size)
                    cout << user.musics[i].name;
            }
        }
        cout << endl;
    }
}

void logAllUsers(vector<User> users)
{
    cout << "ID, Mode, Username, Playlists_number/Songs_number" << endl;
    for (size_t i = 0; i < users.size(); i++)
        logUser(users[i]);
}

void logMusic(Music music, bool __detail = false)
{
    cout << music.id << ", " << music.name << ", " << music.artist;
    if (__detail)
    {
        cout << ", " << music.year << ", " << music.album << ", " << join(music.tags, ";") << ", " << timeToHHMMSS(music.duration);
    }
    cout << endl;
}
void logAllMusics(vector<Music> musics)
{
    cout << "ID, Name, Artist" << endl;
    for (size_t i = 0; i < musics.size(); i++)
        logMusic(musics[i]);
}

void logPlaylist(PlayList playlist)
{
    cout << playlist.name << ", " << playlist.musics.size() << ", " << timeToHHMMSS(playlist.duration, true) << endl;
}
void logAllPlaylists(vector<PlayList> playlists)
{
    cout << "Playlist_name, Songs_number, Duration" << endl;
    for (size_t i = 0; i < playlists.size(); i++)
        logPlaylist(playlists[i]);
}