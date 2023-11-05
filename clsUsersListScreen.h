#pragma once
#include "clsScreen.h"
class clsUsersListScreen : protected clsScreen
{
    static void _PrintUserRecord(clsUser user)
    {
        cout << setw(8) << left << "" << "| " << setw(12) << left << user.username;
        cout << "| " << setw(25) << left << user.FullName();
        cout << "| " << setw(12) << left << user.phone;
        cout << "| " << setw(20) << left << user.email;
        cout << "| " << setw(15) << left << user.password;
        cout << "| " << setw(12) << left << user.permissions;
        cout << endl;
    }
public:
    static void ShowListUsersScreen()
    {
        vector <clsUser> vUsers = clsUser::GetClientList();

        string title = "\t  Client List Screen";
        string subTitle = "\t    (" + to_string(vUsers.size()) + ") Client(s).";

        clsScreen::_DrawScreenHeader(title, subTitle);

        cout << "\n\t_______________________________________________________";
        cout << "___________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(15) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "\n\t_______________________________________________________";
        cout << "___________________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser User : vUsers)
            {
                _PrintUserRecord(User);
            }

        cout << "\n\t_______________________________________________________";
        cout << "___________________________________________________\n" << endl;
    }

};

