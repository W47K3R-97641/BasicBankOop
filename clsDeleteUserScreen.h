#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _PrintUserCard(clsUser user)
    {
        cout << "\nClient Card:";
        cout << "\n-----------------------------------";
        cout << "\nFirst Name  : " << user.firstName;
        cout << "\nLast Name   : " << user.lastName;
        cout << "\nFullName    : " << user.FullName();
        cout << "\nEmail       : " << user.email;
        cout << "\nPhone       : " << user.phone;
        cout << "\nUsername    : " << user.username;
        cout << "\nPassword    : " << user.password;
        cout << "\nPermissions : " << user.permissions;
        cout << "\n-----------------------------------\n";
    }
public:
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\t  Delete Client Screen");

        cout << "\nPlease enter Username : ";
        string username = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(username))
        {
            cout << "\nusername is not found, choose another one : ";
            username = clsInputValidate::ReadString();
        }

        clsUser user = clsUser::Find(username);

        cout << "\nDelete User:\n";
        cout << "\n____________________\n";
        _PrintUserCard(user);

        if (clsUtil::Confirm("\nAre you sure you want to delete this User ?"))
        {
            if (user.Delete())
                cout << "\nUser Deleted Successfully :-)";
            else
                cout << "\nError User Was not Deleted\n";
        }
        else
        {
            cout << "\nUser deletion has been cancelled";

        }
    }
};

