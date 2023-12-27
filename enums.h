#ifndef ENUMS_H
#define ENUMS_H

#include <iostream>
#include <string>

enum Requests
{
    GET,
    POST,
    PUT,
    DELETE
};
int requestVerb(std::string request);

enum ErrorType
{
    BAD_REQUEST_ERROR,
    NOT_FOUND_ERROR,
    PERMISSION_DENIED_ERROR,

    /*
     * special ErrorType
     */
    EMPTY_ERROR,
};
void showErrorMessage(ErrorType errorType);

enum UserMode
{
    USER,
    ARTIST
};

enum Command
{
    POST_SIGNUP,
    POST_LOGIN,
    POST_LOGOUT,

    GET_MUSICS,
    GET_MUSICS_BY_ID,

    GET_USERS,
    GET_USERS_BY_ID,

    POST_PLAYLIST,
    PUT_ADD_PLAYLIST,
    GET_PLAYLIST_BY_ID, //! here id is user id

    GET_SEARCH_MUSIC,

    //* ARTIST SPECIAL COMMANDS
    POST_MUSIC,
    DELETE_MUSIC,
    GET_REGISTERED_MUSICS
};
Command recognizeCommand(std::string command);

#endif