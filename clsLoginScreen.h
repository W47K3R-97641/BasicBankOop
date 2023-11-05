#pragma once
#include <fstream>
#include "Global.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
class clsLoginScreen : protected clsScreen
{

private:
    static  bool _Login()
    {
        bool loginFaild = false;
        short faildLoginCount = 0;

        string username, password;
        do
        {
            if (loginFaild)
            {
                faildLoginCount++;

                cout << "\nInvlaid Username/Password!";
                cout << "\nYou have " << (3 - faildLoginCount)
                    << " Trial(s) to login.\n\n";
            }

            if (faildLoginCount == 3)
            {
                cout << "\nYour are Locked after 3 faild trails \n\n";
                return false;
            }

            cout << "Enter Username: ";
            cin >> username;

            cout << "Enter Password: ";
            cin >> password;

            currentUser = clsUser::Find(username, password);

            loginFaild = currentUser.IsEmpty();

        } while (loginFaild);

        currentUser.RegisterLogIn();

        clsMainScreen::ShowMainMenue();
        return true;
    }
public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();
	}
};

