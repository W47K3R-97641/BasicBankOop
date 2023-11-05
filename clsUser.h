#pragma once
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"

class clsUser : public clsPerson
{
	// Declare Struct stLoginRegisterRecord
	struct stLoginRegisterRecord;
public:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	
	enMode _mode;
	string _username;
	string _password;
	int _permissions;
	bool _markedForDelete = false;
	
	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertUserObjectToLine(clsUser user, string Seperator = "#//#")
	{
		string RecordLine = "";
		RecordLine += user.firstName + Seperator;
		RecordLine += user.lastName + Seperator;
		RecordLine += user.email + Seperator;
		RecordLine += user.phone + Seperator;
		RecordLine += user.username + Seperator;
		RecordLine += clsUtil::EncryptText(user.password) + Seperator;
		RecordLine += to_string(user.permissions);
		return RecordLine;
	}

	static clsUser _ConvertLinetoUserObject(string line, string seperator = "#//#")
	{
		vector<string> vClientData = clsString::Split(line, seperator);

		return clsUser(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], clsUtil::DecryptText(vClientData[5]), stoi(vClientData[6]));
	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		vector <clsUser> vClients;

		fstream myFile;
		myFile.open("Users.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";

			while (getline(myFile, line))
			{
				clsUser client = _ConvertLinetoUserObject(line);
				vClients.push_back(client);
			}

			myFile.close();
		}
		return vClients;
	}

	static void _SaveUsersDataToFile(vector<clsUser> vUsers)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::out);//overwrite

		if (myFile.is_open())
		{
			for (clsUser user : vUsers)
			{
				if (!user.MarkedForDeleted())
				{
					string dataLine = _ConvertUserObjectToLine(user);
					myFile << dataLine << endl;
				}
			}
			myFile.close();
		}
	}

	void _AddDataLineToFile(string dataLine)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << dataLine << endl;
			myFile.close();
		}
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
		//We need to set the mode to update after add new
		_mode = enMode::UpdateMode;
	}

	void _Update()
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& user : vUsers)
		{
			if (user.username == username)
			{
				user = *this;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	string _PrepareLogInRecord(string seperator = "#//#")
	{
		string loginRecord = "";
		loginRecord += clsDate::GetSystemDateTimeNow() + seperator;
		loginRecord += username + seperator;
		loginRecord += clsUtil::EncryptText(password)  + seperator;
		loginRecord += to_string(permissions);
		return loginRecord;
	}
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string line, string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector<string> vLoginRegisterDataLine = clsString::Split(line, Seperator);

		LoginRegisterRecord.dateTime = vLoginRegisterDataLine[0];
		LoginRegisterRecord.username = vLoginRegisterDataLine[1];
		LoginRegisterRecord.password = clsUtil::DecryptText(vLoginRegisterDataLine[2]);
		LoginRegisterRecord.permissions = stoi(vLoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}

public:
	enum enPermissions {
		pAll		  = -1, pListClients = 1,
		pAddNewClient = 2,  pDeleteClient = 4,
		pUpdateClient = 8,  pFindClient = 16,
		pTransactions = 32, pManageUsers = 64,
		pShowLoginRegister = 128 
	};
	
	struct stLoginRegisterRecord
	{
		string dateTime;
		string username;
		string password;
		int permissions;
	};

	clsUser(enMode mode, string firstName, string lastName, string email, string phone, string username, string password, int permissions)
		: clsPerson(firstName, lastName, email, phone)
	{
		_username = username;
		_password = password;
		_permissions = permissions;
		_mode = mode;
	}

	
	bool IsEmpty()
	{
		return (_mode == enMode::EmptyMode);
	}

	void SetUsernname(string username)
	{
		_username = username;
	}
	
	string GetUsername()
	{
		return _username;
	}
	__declspec(property(get = GetUsername, put = SetUsername)) string username;

	void SetPassword(string password)
	{
		_password = password;
	}
	
	string GetPassword()
	{
		return _password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string password;

	void SetPermissions(int permissions)
	{
		_permissions = permissions;
	}
	int GetPermissions()
	{
		return _permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int permissions;

	static clsUser Find(string username)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			while (getline(myFile, line))
			{
				clsUser user = _ConvertLinetoUserObject(line);
				if (user.username == username)
				{
					myFile.close();
					return user;
				}
			}

			myFile.close();
		}

		return _GetEmptyUserObject();
	}
	static clsUser Find(string username, string password)
	{
		clsUser user = clsUser::Find(username);

		if (!user.IsEmpty() && user.password == password)
			return user;

		return _GetEmptyUserObject();
	}

	bool MarkedForDeleted()
	{
		return _markedForDelete;
	}

	static vector <clsUser> GetClientList()
	{
		return _LoadUsersDataFromFile();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUsernameExists = 3 };

	enSaveResults Save()
	{
		switch (_mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
		case enMode::AddNewMode:
			if (clsUser::IsUserExist(username))
			{
				return enSaveResults::svFaildUsernameExists;
			}
			else
			{
				_AddNew();
				return enSaveResults::svSucceeded;
			}

		}
	}

	static bool IsUserExist(string username)
	{
		return !(clsUser::Find(username).IsEmpty());
	}

	bool Delete()
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& user : vUsers)
		{
			if (user.username == username)
			{
				user._markedForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static clsUser GetAddNewUserObject(string username)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", username, "", 0);
	}

	bool CheckAccessPermission(enPermissions permission)
	{

		if (this->permissions == enPermissions::pAll)
			return true;

		if ((permission & this->permissions) == permission)
			return true;

		return false;
	}

	void RegisterLogIn()
	{

		string loginRecord = _PrepareLogInRecord();

		fstream myFile;
		myFile.open("LoginRegister.txt", ios::out | ios::app);

		if (myFile.is_open())
		{

			myFile << loginRecord << endl;

			myFile.close();
		}

	}

	static vector<stLoginRegisterRecord> GetLoginRegisterList()
	{
		fstream myFile;
		
		vector<stLoginRegisterRecord> vLoginRegisterRecord;
		
		myFile.open("LoginRegister.txt", ios::in);
		
		if (myFile.is_open())
		{
			string line = "";
			while (getline(myFile, line))
			{
				stLoginRegisterRecord loginRegisterRecord = _ConvertLoginRegisterLineToRecord(line);
				vLoginRegisterRecord.push_back(loginRegisterRecord);
			}
			myFile.close();
		}

		return vLoginRegisterRecord;
	}
};