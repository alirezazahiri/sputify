#include <iostream>
#include <bits/stdc++.h>

#include "entities.h"
#include "enums.h"
#include "structs.h"
#include "utils.h"
#include "commands.h"

using namespace std;

int main()
{
    while (true)
    {
        try
        {
            vector<User> users = {
                {1, "alirezza.zr2", "SomePassWord2", {false, UserMode::ARTIST}, {}, {}},
                {2, "alirezza.zr3", "SomePassWord", {false, UserMode::USER}, {}, {}},
            };
            vector<Music> Musics;
            int currentUser = -1;

            // signupCommand("POST signup ? username <alirezza.zr> password <SomePassword> mode <user>", &users, &currentUser);

            // loginCommand("POST login ? username <alirezza.zr> password <SomePassword>", &users, &currentUser);
            cout << "------------------------\n";
            cout << currentUser << endl;
            loginCommand("POST login ? username <alirezza.zr2> password <SomePassWord2>", &users, &currentUser);
            cout << currentUser << endl;
            int temp = currentUser;
            logUser(users[temp], false);
            logoutCommand("POST logout ?", &users, &currentUser);
            logUser(users[temp], false);
            cout << currentUser << endl;
            cout << "------------------------\n";
        }
        catch (ErrorType errorType)
        {
            showErrorMessage(errorType);
        }
    }
    return 0;
}