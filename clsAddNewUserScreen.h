#pragma once
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsScreen.h"
class clsAddNewUserScreen : protected clsScreen
{
private:
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
	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\t  Add New User Screen");

		cout << "\nPlease enter username :";
		string username = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(username))
		{
			cout << "\nUsername is already used, choose another one: ";
			username = clsInputValidate::ReadString();
		}

		clsUser newuser = clsUser::GetAddNewUserObject(username);

		_ReadUserInfo(newuser);

		clsUser::enSaveResults saveResult = newuser.Save();

		switch (saveResult)
		{
		case  clsUser::enSaveResults::svSucceeded:
			cout << "\nUser Added successfully :-)\n";
			_PrintUserCard(newuser);
			break;
		case clsUser::enSaveResults::svFaildEmptyObject:
			cout << "\nError User was not saved because it's Empty";
			break;
		case clsUser::svFaildUsernameExists:
			cout << "\nError account was not saved because username is used!\n";
			break;
		}

	}
};

