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

int requestVerb(std::string request)
{
    if (request == "GET")
        return Requests::GET;
    else if (request == "POST")
        return Requests::POST;
    else if (request == "PUT")
        return Requests::PUT;
    else if (request == "DELETE")
        return Requests::DELETE;
    return -1;
}

void showErrorMessage(ErrorType errorType)
{
    switch (errorType)
    {
    case ErrorType::BAD_REQUEST_ERROR:
        std::cout << "Bad Request";
        break;
    case ErrorType::NOT_FOUND_ERROR:
        std::cout << "Not Found";
        break;
    case ErrorType::PERMISSION_DENIED_ERROR:
        std::cout << "Permission Denied";
        break;
    case ErrorType::EMPTY_ERROR:
        std::cout << "Empty";
        break;
    default:
        std::cout << "Not Implemented";
        break;
    }
    std::cout << std::endl;
}

#endif