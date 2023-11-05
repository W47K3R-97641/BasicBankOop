#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageUsersMenue : protected clsScreen
{
private:
    enum enManageUsersMenueOptions {
        eListUsers = 1, eAddNewUser = 2,
        eDeleteUser = 3, eUpdateUser = 4,
        eFindUser = 5, eMainMenue = 6
    };

    static enManageUsersMenueOptions _ReadManageUsersMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";

        enManageUsersMenueOptions choice = (enManageUsersMenueOptions)clsInputValidate::ReadIntBetween(1, 6, "Enter Number between 1 to 6?");
        return choice;
    }

    static void _GoBackToManageUsersMenue()
    {
        cout << "\n\nPress any key to go back to Manage Users Menue...";
        system("pause>0");
        ShowManageUsersMenue();
    }

    static void _ShowListUsersScreen()
    {
        clsUsersListScreen::ShowListUsersScreen();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindClientScreen();
    }

    static void _PerformdManageUsersMenueOption(enManageUsersMenueOptions manageUsersOption)
    {
        system("cls");
        switch (manageUsersOption)
        {
        case clsManageUsersMenue::eListUsers:
            _ShowListUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUsersMenue::eAddNewUser:
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUsersMenue::eDeleteUser:
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUsersMenue::eUpdateUser:
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUsersMenue::eFindUser:
            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUsersMenue::eMainMenue:
            break;
        }
    }
public:
    static void ShowManageUsersMenue()
    {
        if (!_CheckAccessRight(clsUser::enPermissions::pManageUsers))
            return;

        system("cls");
        _DrawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformdManageUsersMenueOption(_ReadManageUsersMenueOption());
    }
};

