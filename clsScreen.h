#pragma once
#include <iomanip>
#include "clsUser.h"
#include "clsDate.h"
#include "Global.h"
class clsScreen
{
protected:
    static void _DrawScreenHeader(string title, string subTitle = "")
    {
        cout << setw(37) << left << "" << "Date: " << clsDate::DateToString(clsDate());
        
        if (!currentUser.IsEmpty())
            cout << setw(14)  << left  << ""  << "User: " << currentUser.username;

        cout << "\n" << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t" << title << "\n";
        if (subTitle != "")
        {
            cout << setw(37) << left << "" << "\t" << subTitle << "\n";
        }
        
        cout << setw(37) << left << "" << "===========================================\n";
    }

    static bool _CheckAccessRight(clsUser::enPermissions permission)
    {

        if (!currentUser.CheckAccessPermission(permission))
        {
            _DrawScreenHeader("Access Denied Contact Your Admin !");
            return false;
        }
        return true;

    }
};

