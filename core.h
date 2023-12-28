#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <string>
#include <vector>

#include "enums.h"
#include "entities.h"
#include "helpers.h"
#include "commands.h"

Command recognizeCommand(std::string command)
{
    std::vector<std::string> tokens = tokenize(command);
    size_t size = tokens.size();

    if (tokens.size() < 3)
        throw ErrorType::BAD_REQUEST_ERROR;

    if (tokens[0] == "GET")
    {
        if (tokens[1] == "musics")
        {
            if (tokens.size() > 3)
            {
                if (tokens[3] == "id")
                    return Command::GET_MUSICS_BY_ID;
                else
                    throw ErrorType::BAD_REQUEST_ERROR;
            }
            else
            {
                return Command::GET_MUSICS;
            }
        }
        else if (tokens[1] == "users")
        {
            if (tokens.size() > 3)
            {
                if (tokens[3] == "id")
                    return Command::GET_USERS_BY_ID;
                else
                    throw ErrorType::BAD_REQUEST_ERROR;
            }
            else
            {
                return Command::GET_USERS;
            }
        }
        else if (tokens[1] == "playlist")
        {
            if (tokens.size() > 3)
            {
                if (tokens[3] == "id")
                    return Command::GET_PLAYLIST_BY_ID;
                else
                    throw ErrorType::BAD_REQUEST_ERROR;
            }
            else
            {
                throw ErrorType::BAD_REQUEST_ERROR;
            }
        }
        else if (tokens[1] == "search_music")
        {
            if (tokens.size() > 4)
            {
                return Command::GET_SEARCH_MUSIC;
            }
            else
            {
                throw ErrorType::BAD_REQUEST_ERROR;
            }
        }
        else if (tokens[1] == "registered_musics")
        {
            return Command::GET_REGISTERED_MUSICS;
        }
        else
            throw ErrorType::NOT_FOUND_ERROR;
    }
    else if (tokens[0] == "POST")
    {
        if (tokens[1] == "signup")
        {
            return Command::POST_SIGNUP;
        }
        else if (tokens[1] == "login")
        {
            return Command::POST_LOGIN;
        }
        else if (tokens[1] == "logout")
        {
            return Command::POST_LOGOUT;
        }
        else if (tokens[1] == "playlist")
        {
            return Command::POST_PLAYLIST;
        }
        else if (tokens[1] == "music")
        {
            return Command::POST_MUSIC;
        }
        else
            throw ErrorType::NOT_FOUND_ERROR;
    }
    else if (tokens[0] == "PUT")
    {
        if (tokens[1] == "add_playlist")
        {
            return Command::PUT_ADD_PLAYLIST;
        }
        else
            throw ErrorType::NOT_FOUND_ERROR;
    }
    else if (tokens[0] == "DELETE")
    {
        if (tokens[1] == "music")
        {
            return Command::DELETE_MUSIC;
        }
        else
            throw ErrorType::NOT_FOUND_ERROR;
    }
    else
        throw ErrorType::BAD_REQUEST_ERROR;
}

void execute(Command command, std::string input, std::vector<User> *users, std::vector<Music> *musics, int *currentUser, int *latestMusicID)
{
    switch (command)
    {
    case Command::GET_MUSICS:
        // std::cout << "Command::GET_MUSICS" << std::endl;
        getMusicsCommand(input, users, currentUser, musics);
        break;
    case Command::GET_MUSICS_BY_ID:
        // std::cout << "Command::GET_MUSICS_BY_ID" << std::endl;
        getMusicByIdCommand(input, users, currentUser, musics);
        break;
    case Command::GET_PLAYLIST_BY_ID:
        // std::cout << "Command::GET_PLAYLIST_BY_ID" << std::endl;
        getUserPlaylistsCommand(input, users, currentUser);
        break;
    case Command::GET_REGISTERED_MUSICS:
        // std::cout << "Command::GET_REGISTERED_MUSICS" << std::endl;
        showRegisteredMusicsCommand(input, users, currentUser, musics);
        break;
    case Command::GET_SEARCH_MUSIC:
        // std::cout << "Command::GET_SEARCH_MUSIC" << std::endl;
        searchMusicCommand(input, users, currentUser, musics);
        break;
    case Command::GET_USERS:
        // std::cout << "Command::GET_USERS " << std::endl;
        getAllUsersCommand(input, users, currentUser);
        break;
    case Command::GET_USERS_BY_ID:
        // std::cout << "Command::GET_USERS_BY_ID" << std::endl;
        getUserByIdCommand(input, users, currentUser);
        break;
    case Command::POST_LOGIN:
        // std::cout << "Command::POST_LOGIN" << std::endl;
        loginCommand(input, users, currentUser);
        break;
    case Command::POST_LOGOUT:
        // std::cout << "Command::POST_LOGOUT" << std::endl;
        logoutCommand(input, users, currentUser);
        break;
    case Command::POST_SIGNUP:
        // std::cout << "Command::POST_SIGNUP" << std::endl;
        signupCommand(input, users, currentUser);
        break;
    case Command::POST_MUSIC:
        // std::cout << "Command::POST_MUSIC" << std::endl;
        shareMusicCommand(input, users, currentUser, musics, latestMusicID);
        break;
    case Command::POST_PLAYLIST:
        // std::cout << "Command::POST_PLAYLIST" << std::endl;
        createPlaylistCommand(input, users, currentUser);
        break;
    case Command::PUT_ADD_PLAYLIST:
        // std::cout << "Command::PUT_ADD_PLAYLIST" << std::endl;
        addMusicToPlaylistCommand(input, users, currentUser, musics);
        break;
    case Command::DELETE_MUSIC:
        // std::cout << "Command::DELETE_MUSIC" << std::endl;
        deleteMusicCommand(input, users, currentUser, musics);
        break;
    default:
        throw ErrorType::BAD_REQUEST_ERROR;
    }
}

#endif