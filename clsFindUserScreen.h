#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsFindUserScreen : protected clsScreen
{
private:
	static void _PrintUserCard(clsUser user)
	{
		cout << "\nUser Card:";
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
	static void ShowFindClientScreen()
	{
		_DrawScreenHeader("\t  Find User Screen");

		cout << "\nPlease Enter Username: ";
		string username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(username))
		{
			cout << "\nusername is not found, choose another one: ";
			username = clsInputValidate::ReadString();
		}

		clsUser user = clsUser::Find(username);

		if (!user.IsEmpty())
		{
			cout << "\nUser Found :-)\n";
			_PrintUserCard(user);
		}
		else
		{
			cout << "\nUser Was not Found :-(\n";
		}

	}
};

