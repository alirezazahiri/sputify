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

#endif