#pragma once
#include "clsScreen.h"

class clsLoginRegisterScreen : protected clsScreen
{
	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord loginRegisterRecord)
	{
		
		cout << "\t";

		cout << "| " << setw(30) << left << loginRegisterRecord.dateTime;    
		cout << "| " << setw(20) << left << loginRegisterRecord.username;   
		cout << "| " << setw(20) << left << loginRegisterRecord.password;      
		cout << "| " << setw(10) << left << loginRegisterRecord.permissions; 

		cout << endl;
	}
public:
	static void ShowLoginRegisterScreen()
	{

		if (!_CheckAccessRight(clsUser::enPermissions::pShowLoginRegister))
			return;

		vector<clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

		string title = "\t  Login Register List Screen";
		string subTitle = "\t    (" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";
		clsScreen::_DrawScreenHeader(title, subTitle);
		
		cout << "\n\t_______________________________________________________________________________________________\n\t";		
		cout << "| " << setw(30) << left << "DATE/TIME";
		cout << "| " << setw(20) << left << "USERNAME";
		cout << "| " << setw(20) << left << "PASSWORD";
		cout << "| " << setw(10) << left << "Permissions";
		cout << "\n\t_______________________________________________________________________________________________\n";
		
		if (vLoginRegisterRecord.size() == 0)
			cout << "\t\t\t\tNo Logins Available In the System!";

		for (clsUser::stLoginRegisterRecord record : vLoginRegisterRecord)
		{
			_PrintLoginRegisterRecordLine(record);
		}
		cout << "\t_______________________________________________________________________________________________\n";

	}
};

