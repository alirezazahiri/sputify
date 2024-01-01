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
    POST_LIKE_MUSIC_BY_ID,

    GET_USERS,
    GET_USERS_BY_ID,

    POST_PLAYLIST,
    PUT_ADD_PLAYLIST,
    GET_PLAYLIST_BY_USER_ID,
    GET_PLAYLIST_BY_NAME_AND_USER_ID,
    DELETE_PLAYLIST_BY_ID,

    GET_SEARCH_MUSIC,

    //* ARTIST SPECIAL COMMANDS
    POST_MUSIC,
    DELETE_MUSIC,
    GET_REGISTERED_MUSICS,

    //* follow/unfollow mechanism
    POST_FOLLOW_BY_ID,
    POST_UNFOLLOW_BY_ID,

    //TODO: recommendations
    GET_RECOMMENDATIONS,
    GET_LIKES
};
Command recognizeCommand(std::string command);

#endif