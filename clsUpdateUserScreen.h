#pragma once
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsUpdateUserScreen : protected clsScreen
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
	static int  _ReadPermissionsToSet()
	{
		if (clsUtil::Confirm("\nDo You Want To Give Full Access ?"))
		{
			return clsUser::pAll;
		}

		int permissions = 0;

		permissions += clsUtil::Confirm("\nShow Client List ?") ? clsUser::pListClients : 0;
		permissions += clsUtil::Confirm("\nAdd New Client ?") ? clsUser::pAddNewClient : 0;
		permissions += clsUtil::Confirm("\nDelete Client ?") ? clsUser::pDeleteClient : 0;
		permissions += clsUtil::Confirm("\nUpdate Client ?") ? clsUser::pUpdateClient : 0;
		permissions += clsUtil::Confirm("\nFind Client ?") ? clsUser::pFindClient : 0;
		permissions += clsUtil::Confirm("\nTransactions ?") ? clsUser::pTransactions : 0;
		permissions += clsUtil::Confirm("\nManage Users ?") ? clsUser::pManageUsers : 0;
		permissions += clsUtil::Confirm("\nShow Login Register ?") ? clsUser::pShowLoginRegister : 0;


		return permissions;
	}
	static void _ReadUserInfo(clsUser& user)
	{
		cout << "\nEnter FirstName:";
		user.firstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName:";
		user.lastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		user.email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		user.phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		user.password = clsInputValidate::ReadString();

		user.permissions = _ReadPermissionsToSet();
	}
public:
	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\t  Update User Screen");

		cout << "\nPlease Enter Username: ";
		string username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(username))
		{
			cout << "\nusername is not found, choose another one : ";
			username = clsInputValidate::ReadString();
		}

		clsUser user = clsUser::Find(username);
		_PrintUserCard(user);

		if (clsUtil::Confirm("\nAre You Sure Do you Want to Update This User ?"))
		{
			cout << "\nUpdate User:\n";
			cout << "\n____________________\n";

			_ReadUserInfo(user);

			clsUser::enSaveResults saveResult = user.Save();

			switch (saveResult)
			{
			case  clsBankClient::enSaveResults::svSucceeded:
				cout << "\nUser updated successfully :-)\n";
				_PrintUserCard(user);
				break;
			case clsBankClient::enSaveResults::svFaildEmptyObject:
				cout << "\nError User was not saved because it's Empty";
				break;
			}
		}
		else
		{
			cout << "\nuser update has been cancelled.\n";
		}


	}
};