#include <iostream>
#include <string>
#include <vector>

#include "enums.h"
#include "utils.h"
#include "commands.h"
#include "core.h"
#include "entities.h"

using namespace std;

int main()
{
    vector<User> users;
    vector<Music> musics;

    int currentUser = -1;
    int latestMusicID = 0;

    while (true)
    {
        try
        {
            string input;
            getline(cin, input);
            Command cmd = recognizeCommand(input);
            execute(cmd, input, &users, &musics, &currentUser, &latestMusicID);

            cout << currentUser << endl;
        }
        catch (ErrorType errorType)
        {
            showErrorMessage(errorType);
        }
    }
    return 0;
}